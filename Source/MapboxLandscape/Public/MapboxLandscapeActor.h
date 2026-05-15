#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "MapboxLandscapeActor.generated.h"

UENUM(BlueprintType)
enum class ECoordinateMode : uint8
{
	BoundingBox UMETA(DisplayName = "Bounding Box (N/S/E/W)"),
	CenterRadius UMETA(DisplayName = "Center Point & Radius"),
	ToolString UMETA(DisplayName = "Tool String (maps.ludicdrive.com)")
};

UCLASS()
class MAPBOXLANDSCAPE_API AMapboxLandscapeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapboxLandscapeActor();

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings")
	FString ApiKey;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates")
	ECoordinateMode CoordinateMode = ECoordinateMode::BoundingBox;

	// Bounding Box Mode
	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox"))
	double North = 36.17;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox"))
	double South = 36.15;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox"))
	double East = -86.77;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox"))
	double West = -86.79;

	// Center & Radius Mode
	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius"))
	double CenterLatitude = 36.16;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius"))
	double CenterLongitude = -86.78;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius"))
	double RadiusKm = 1.0;

	// Tool String Mode
	UPROPERTY(EditAnywhere, Category = "Mapbox Settings | Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::ToolString"))
	FString CoordinateString;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings")
	int32 ZoomLevel = 15;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings")
	bool bImportSatellite = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings")
	UMaterialInterface* BaseMaterial;

	UPROPERTY(EditAnywhere, Category = "Mapbox Settings")
	FString MetadataStyleId = TEXT("mapbox/streets-v11");

	UFUNCTION(CallInEditor, Category = "Mapbox Actions")
	void FetchLandscape();

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif

private:
	void DownloadHeightTile(int32 X, int32 Y, int32 Z);
	void OnHeightTileDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, int32 X, int32 Y);

	void DownloadMetadataTile(int32 X, int32 Y, int32 Z);
	void OnMetadataTileDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, int32 X, int32 Y);

	void DownloadSatelliteTile(int32 X, int32 Y, int32 Z);
	void OnSatelliteTileDownloaded(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, int32 X, int32 Y);

	struct FTileData
	{
		TArray<uint8> RawData;
		int32 X, Y;
	};

	TArray<FTileData> DownloadedHeightTiles;
	TArray<FTileData> DownloadedMetadataTiles;
	TArray<FTileData> DownloadedSatelliteTiles;
	
	int32 PendingHeightRequests = 0;
	int32 PendingMetadataRequests = 0;
	int32 PendingSatelliteRequests = 0;
	bool bIsFetching = false;

	int32 MinTileX, MaxTileX, MinTileY, MaxTileY;

	void FinishFetch();
	void CheckAllTilesDownloaded();
	void ProcessTiles();
	uint16 DecodeHeight(uint8 R, uint8 G, uint8 B);

	void CreateLandscape(const TArray<uint16>& HeightData, const TArray<FColor>& MetadataData, UTexture2D* SatelliteTexture, int32 Width, int32 Height);
};
