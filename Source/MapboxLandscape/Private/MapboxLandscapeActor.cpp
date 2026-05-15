#include "MapboxLandscapeActor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
#include "Landscape.h"
#include "LandscapeEditLayer.h"
#include "LandscapeInfo.h"
#include "Editor.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "LandscapeLayerInfoObject.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "FileHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture2D.h"

AMapboxLandscapeActor::AMapboxLandscapeActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMapboxLandscapeActor::BeginPlay()
{
	Super::BeginPlay();
}

#if WITH_EDITOR
bool AMapboxLandscapeActor::CanEditChange(const FProperty* InProperty) const
{
	return !bIsFetching && Super::CanEditChange(InProperty);
}
#endif

int32 LonToTileX(double lon, int z) {
	return (int32)(FMath::Floor((lon + 180.0) / 360.0 * FMath::Pow(2.0, z)));
}

int32 LatToTileY(double lat, int z) {
	return (int32)(FMath::Floor((1.0 - FMath::Loge(FMath::Tan(FMath::DegreesToRadians(lat)) + 1.0 / FMath::Cos(FMath::DegreesToRadians(lat))) / PI) / 2.0 * FMath::Pow(2.0, z)));
}

void AMapboxLandscapeActor::FetchLandscape()
{
	if (bIsFetching)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mapbox fetch is already in progress."));
		return;
	}

	if (ApiKey.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Mapbox API Key is empty!"));
		return;
	}

	bIsFetching = true;

	double FinalNorth = North;
	double FinalSouth = South;
	double FinalEast = East;
	double FinalWest = West;

	if (CoordinateMode == ECoordinateMode::CenterRadius)
	{
		if (RadiusKm <= 0.0 || CenterLatitude <= -89.0 || CenterLatitude >= 89.0)
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid center/radius settings. Radius must be greater than zero and latitude must be between -89 and 89 degrees."));
			FinishFetch();
			return;
		}

		double DeltaLat = RadiusKm / 111.32;
		double DeltaLng = RadiusKm / (111.32 * FMath::Cos(FMath::DegreesToRadians(CenterLatitude)));
		FinalNorth = CenterLatitude + DeltaLat;
		FinalSouth = CenterLatitude - DeltaLat;
		FinalEast = CenterLongitude + DeltaLng;
		FinalWest = CenterLongitude - DeltaLng;
	}
	else if (CoordinateMode == ECoordinateMode::ToolString)
	{
		TArray<FString> Parts;
		CoordinateString.Replace(TEXT(" "), TEXT(",")).ParseIntoArray(Parts, TEXT(","), true);
		if (Parts.Num() >= 4)
		{
			TArray<double> Values;
			for (const FString& P : Parts) { Values.Add(FCString::Atod(*P.TrimStartAndEnd())); }

			TArray<double> GroupA; // Evens
			TArray<double> GroupB; // Odds
			for (int32 i = 0; i < Values.Num(); ++i)
			{
				if (i % 2 == 0) GroupA.Add(Values[i]);
				else GroupB.Add(Values[i]);
			}

			// Heuristic: Check which group is more likely to be Latitude (-90 to 90)
			bool bGroupAIsLat = true;
			bool bAInLatRange = true;
			for (double V : GroupA) { if (V < -90.0 || V > 90.0) { bAInLatRange = false; break; } }
			bool bBInLatRange = true;
			for (double V : GroupB) { if (V < -90.0 || V > 90.0) { bBInLatRange = false; break; } }

			if (!bAInLatRange && bBInLatRange) bGroupAIsLat = false;
			else if (bAInLatRange && !bBInLatRange) bGroupAIsLat = true;
			else bGroupAIsLat = true; // Default to first is Lat

			TArray<double>& Lats = bGroupAIsLat ? GroupA : GroupB;
			TArray<double>& Lngs = bGroupAIsLat ? GroupB : GroupA;

			FinalSouth = Lats[0]; FinalNorth = Lats[0];
			FinalWest = Lngs[0]; FinalEast = Lngs[0];
			for (double V : Lats) { FinalSouth = FMath::Min(FinalSouth, V); FinalNorth = FMath::Max(FinalNorth, V); }
			for (double V : Lats) { FinalNorth = FMath::Max(FinalNorth, V); }
			for (double V : Lngs) { FinalWest = FMath::Min(FinalWest, V); FinalEast = FMath::Max(FinalEast, V); }
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not parse Coordinate String. Expected at least 4 comma-separated values."));
			FinishFetch();
			return;
		}
	}

	DownloadedHeightTiles.Empty();
	DownloadedMetadataTiles.Empty();
	DownloadedSatelliteTiles.Empty();
	
	MinTileX = LonToTileX(FinalWest, ZoomLevel);
	MaxTileX = LonToTileX(FinalEast, ZoomLevel);
	MinTileY = LatToTileY(FinalNorth, ZoomLevel);
	MaxTileY = LatToTileY(FinalSouth, ZoomLevel);

	// Ensure Min < Max for tile indices
	if (MinTileX > MaxTileX) { int32 T = MinTileX; MinTileX = MaxTileX; MaxTileX = T; }
	if (MinTileY > MaxTileY) { int32 T = MinTileY; MinTileY = MaxTileY; MaxTileY = T; }

	int32 TilesXCount = (MaxTileX - MinTileX) + 1;
	int32 TilesYCount = (MaxTileY - MinTileY) + 1;
	if (TilesXCount <= 0 || TilesYCount <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Mapbox import aborted: invalid tile range."));
		FinishFetch();
		return;
	}

	PendingHeightRequests = TilesXCount * TilesYCount;
	PendingMetadataRequests = TilesXCount * TilesYCount;
	PendingSatelliteRequests = bImportSatellite ? (TilesXCount * TilesYCount) : 0;

	UE_LOG(LogTemp, Log, TEXT("Fetching %d x %d tiles..."), TilesXCount, TilesYCount);

	for (int32 x = MinTileX; x <= MaxTileX; ++x)
	{
		for (int32 y = MinTileY; y <= MaxTileY; ++y)
		{
			DownloadHeightTile(x, y, ZoomLevel);
			DownloadMetadataTile(x, y, ZoomLevel);
			if (bImportSatellite) DownloadSatelliteTile(x, y, ZoomLevel);
		}
	}
}

void AMapboxLandscapeActor::DownloadHeightTile(int32 X, int32 Y, int32 Z)
{
	FString Url = FString::Printf(TEXT("https://api.mapbox.com/v4/mapbox.terrain-rgb/%d/%d/%d.pngraw?access_token=%s"), Z, X, Y, *ApiKey);
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AMapboxLandscapeActor::OnHeightTileDownloaded, X, Y);
	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));
	Request->ProcessRequest();
}

void AMapboxLandscapeActor::OnHeightTileDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, int32 X, int32 Y)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FTileData Tile; Tile.X = X; Tile.Y = Y; Tile.RawData = Response->GetContent();
		DownloadedHeightTiles.Add(Tile);
	}
	PendingHeightRequests--;
	CheckAllTilesDownloaded();
}

void AMapboxLandscapeActor::DownloadMetadataTile(int32 X, int32 Y, int32 Z)
{
	FString Url = FString::Printf(TEXT("https://api.mapbox.com/styles/v1/%s/tiles/%d/%d/%d?access_token=%s"), *MetadataStyleId, Z, X, Y, *ApiKey);
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AMapboxLandscapeActor::OnMetadataTileDownloaded, X, Y);
	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));
	Request->ProcessRequest();
}

void AMapboxLandscapeActor::OnMetadataTileDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, int32 X, int32 Y)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FTileData Tile; Tile.X = X; Tile.Y = Y; Tile.RawData = Response->GetContent();
		DownloadedMetadataTiles.Add(Tile);
	}
	PendingMetadataRequests--;
	CheckAllTilesDownloaded();
}

void AMapboxLandscapeActor::DownloadSatelliteTile(int32 X, int32 Y, int32 Z)
{
	FString Url = FString::Printf(TEXT("https://api.mapbox.com/v4/mapbox.satellite/%d/%d/%d.png?access_token=%s"), Z, X, Y, *ApiKey);
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AMapboxLandscapeActor::OnSatelliteTileDownloaded, X, Y);
	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));
	Request->ProcessRequest();
}

void AMapboxLandscapeActor::OnSatelliteTileDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, int32 X, int32 Y)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FTileData Tile; Tile.X = X; Tile.Y = Y; Tile.RawData = Response->GetContent();
		DownloadedSatelliteTiles.Add(Tile);
	}
	PendingSatelliteRequests--;
	CheckAllTilesDownloaded();
}

void AMapboxLandscapeActor::CheckAllTilesDownloaded()
{
	if (PendingHeightRequests == 0 && PendingMetadataRequests == 0 && PendingSatelliteRequests == 0)
	{
		ProcessTiles();
		FinishFetch();
	}
}

void AMapboxLandscapeActor::FinishFetch()
{
	PendingHeightRequests = 0;
	PendingMetadataRequests = 0;
	PendingSatelliteRequests = 0;
	bIsFetching = false;
}

void AMapboxLandscapeActor::ProcessTiles()
{
	auto SortTiles = [](TArray<FTileData>& Tiles) {
		Tiles.Sort([](const FTileData& A, const FTileData& B) {
			if (A.Y != B.Y) return A.Y < B.Y;
			return A.X < B.X;
		});
	};

	SortTiles(DownloadedHeightTiles);
	SortTiles(DownloadedMetadataTiles);
	SortTiles(DownloadedSatelliteTiles);

	const int32 TileSize = 256;
	int32 TilesXCount = (MaxTileX - MinTileX) + 1;
	int32 TilesYCount = (MaxTileY - MinTileY) + 1;
	int32 TotalWidth = TilesXCount * TileSize;
	int32 TotalHeight = TilesYCount * TileSize;
	const int32 ExpectedTileCount = TilesXCount * TilesYCount;

	if (DownloadedHeightTiles.Num() != ExpectedTileCount || DownloadedMetadataTiles.Num() != ExpectedTileCount || (bImportSatellite && DownloadedSatelliteTiles.Num() != ExpectedTileCount))
	{
		UE_LOG(LogTemp, Error, TEXT("Mapbox import aborted: expected %d tiles, got height=%d metadata=%d satellite=%d."),
			ExpectedTileCount, DownloadedHeightTiles.Num(), DownloadedMetadataTiles.Num(), DownloadedSatelliteTiles.Num());
		return;
	}

	TArray<uint16> FullHeightData; FullHeightData.SetNumUninitialized(TotalWidth * TotalHeight);
	TArray<FColor> FullMetadataData; FullMetadataData.SetNumUninitialized(TotalWidth * TotalHeight);
	TArray<FColor> FullSatelliteData; if (bImportSatellite) FullSatelliteData.SetNumUninitialized(TotalWidth * TotalHeight);

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	
	auto ProcessTileSet = [&](TArray<FTileData>& Tiles, auto PixelProcessor) {
		for (const auto& Tile : Tiles) {
			TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(Tile.RawData.Num() > 4 && Tile.RawData[0] == 0xFF && Tile.RawData[1] == 0xD8 ? EImageFormat::JPEG : EImageFormat::PNG);
			
			if (ImageWrapper->SetCompressed(Tile.RawData.GetData(), Tile.RawData.Num())) {
				TArray<uint8> RawRGBA;
				if (ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, RawRGBA)) {
					if (RawRGBA.Num() < TileSize * TileSize * 4)
					{
						UE_LOG(LogTemp, Error, TEXT("Mapbox import aborted: decoded tile %d/%d is smaller than expected."), Tile.X, Tile.Y);
						return false;
					}

					int32 LocalStartX = (Tile.X - MinTileX) * TileSize;
					int32 LocalStartY = (Tile.Y - MinTileY) * TileSize;
					for (int32 py = 0; py < TileSize; ++py) {
						for (int32 px = 0; px < TileSize; ++px) {
							int32 rgbaIdx = (py * TileSize + px) * 4;
							PixelProcessor(LocalStartX + px, LocalStartY + py, RawRGBA[rgbaIdx], RawRGBA[rgbaIdx+1], RawRGBA[rgbaIdx+2], RawRGBA[rgbaIdx+3]);
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Mapbox import aborted: failed to decode tile %d/%d."), Tile.X, Tile.Y);
					return false;
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Mapbox import aborted: failed to parse tile %d/%d."), Tile.X, Tile.Y);
				return false;
			}
		}
		return true;
	};

	if (!ProcessTileSet(DownloadedHeightTiles, [&](int x, int y, uint8 r, uint8 g, uint8 b, uint8 a) {
		FullHeightData[y * TotalWidth + x] = DecodeHeight(r, g, b);
	}))
	{
		return;
	}

	if (!ProcessTileSet(DownloadedMetadataTiles, [&](int x, int y, uint8 r, uint8 g, uint8 b, uint8 a) {
		FullMetadataData[y * TotalWidth + x] = FColor(r, g, b, 255);
	}))
	{
		return;
	}

	if (bImportSatellite) {
		if (!ProcessTileSet(DownloadedSatelliteTiles, [&](int x, int y, uint8 r, uint8 g, uint8 b, uint8 a) {
			FullSatelliteData[y * TotalWidth + x] = FColor(r, g, b, 255);
		}))
		{
			return;
		}
	}

	UTexture2D* SatelliteTex = nullptr;
	if (bImportSatellite) {
		SatelliteTex = UTexture2D::CreateTransient(TotalWidth, TotalHeight, PF_B8G8R8A8);
		FTexture2DMipMap& Mip = SatelliteTex->GetPlatformData()->Mips[0];
		void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(Data, FullSatelliteData.GetData(), FullSatelliteData.Num() * sizeof(FColor));
		Mip.BulkData.Unlock();
		SatelliteTex->UpdateResource();
	}

	CreateLandscape(FullHeightData, FullMetadataData, SatelliteTex, TotalWidth, TotalHeight);
}

uint16 AMapboxLandscapeActor::DecodeHeight(uint8 R, uint8 G, uint8 B)
{
	float Meters = -10000.0f + ((R * 65536.0f + G * 256.0f + B) * 0.1f);
	float UnrealUnits = Meters * 100.0f;
	return (uint16)FMath::Clamp(FMath::RoundToInt(UnrealUnits) + 32768, 0, 65535);
}

void AMapboxLandscapeActor::CreateLandscape(const TArray<uint16>& HeightData, const TArray<FColor>& MetadataData, UTexture2D* SatelliteTexture, int32 Width, int32 Height)
{
	UWorld* World = GetWorld();
	if (!World) return;

	int32 SectionSize = 63;
	int32 SectionsPerComponent = 1;
	int32 ComponentCountX = (Width - 1) / SectionSize;
	int32 ComponentCountY = (Height - 1) / SectionSize;
	int32 NewWidth = ComponentCountX * SectionSize + 1;
	int32 NewHeight = ComponentCountY * SectionSize + 1;

	TArray<uint16> ResizedHeightData; ResizedHeightData.SetNumUninitialized(NewWidth * NewHeight);
	TArray<FName> LayerNames = { TEXT("Forest"), TEXT("Urban"), TEXT("Road"), TEXT("Water") };
	TMap<FName, TArray<uint8>> LayerDataMap;
	for (FName Name : LayerNames) { LayerDataMap.Add(Name).SetNumZeroed(NewWidth * NewHeight); }

	for (int32 y = 0; y < NewHeight; ++y) {
		for (int32 x = 0; x < NewWidth; ++x) {
			int32 ClampedX = FMath::Min(x, Width - 1);
			int32 ClampedY = FMath::Min(y, Height - 1);
			int32 Idx = ClampedY * Width + ClampedX;
			int32 NewIdx = y * NewWidth + x;
			ResizedHeightData[NewIdx] = HeightData[Idx];
			FColor Color = MetadataData[Idx];
			if (Color.G > Color.R + 50 && Color.G > Color.B + 50) LayerDataMap[TEXT("Forest")][NewIdx] = 255;
			else if (Color.R > 100 && Color.G > 100 && Color.B > 100 && FMath::Abs(Color.R - Color.G) < 20) LayerDataMap[TEXT("Urban")][NewIdx] = 255;
			else if (Color.B > Color.R + 50 && Color.B > Color.G + 50) LayerDataMap[TEXT("Water")][NewIdx] = 255;
			else LayerDataMap[TEXT("Road")][NewIdx] = 255;
		}
	}

	ALandscape* Landscape = World->SpawnActor<ALandscape>();
	if (!Landscape) return;
	Landscape->SetActorLabel(TEXT("MapboxLandscape"));
	Landscape->SetActorTransform(FTransform(FRotator::ZeroRotator, GetActorLocation(), FVector(100.f, 100.f, 100.f)));

	if (BaseMaterial && SatelliteTexture) {
		UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		DynMat->SetTextureParameterValue(TEXT("SatelliteTex"), SatelliteTexture);
		Landscape->LandscapeMaterial = DynMat;
	}

	const FGuid LayerGuid;

	TMap<FGuid, TArray<uint16>> HeightDataPerLayers;
	HeightDataPerLayers.Add(LayerGuid, ResizedHeightData);

	TMap<FGuid, TArray<FLandscapeImportLayerInfo>> MaterialLayerDataPerLayers;
	TArray<FLandscapeImportLayerInfo> LayerInfos;
	for (auto& Pair : LayerDataMap) {
		FLandscapeImportLayerInfo LayerInfo;
		LayerInfo.LayerName = Pair.Key;
		LayerInfo.LayerInfo = NewObject<ULandscapeLayerInfoObject>(Landscape, Pair.Key);
		LayerInfo.LayerInfo->SetLayerName(Pair.Key, /*bInModify = */false);
		LayerInfo.LayerData = Pair.Value;
		LayerInfos.Add(LayerInfo);
	}
	MaterialLayerDataPerLayers.Add(LayerGuid, LayerInfos);

#if WITH_EDITOR
	Landscape->Import(FGuid::NewGuid(), 0, 0, NewWidth - 1, NewHeight - 1, SectionsPerComponent, SectionSize, HeightDataPerLayers, TEXT(""), MaterialLayerDataPerLayers, ELandscapeImportAlphamapType::Additive, TArrayView<const FLandscapeLayer>());
#endif

	UE_LOG(LogTemp, Log, TEXT("Landscape Created from Bounding Box!"));
}
