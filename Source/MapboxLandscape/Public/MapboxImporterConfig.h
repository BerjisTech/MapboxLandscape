#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interfaces/IHttpRequest.h"
#include "Materials/MaterialInterface.h"
#include "MapboxLayerDef.h"
#include "MapboxImporterConfig.generated.h"

class UPCGGraphInterface;
class ALandscape;
class UTexture2D;
class UWorld;

UENUM(BlueprintType)
enum class ECoordinateMode : uint8
{
	CenterRadius UMETA(DisplayName = "Center Point & Radius"),
	BoundingBox  UMETA(DisplayName = "Bounding Box (N/S/E/W)"),
	ToolString   UMETA(DisplayName = "Tool String (comma-separated lat/lng)")
};

USTRUCT(BlueprintType)
struct FMapboxTileResult
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Tile")
	int32 TileGridX = 0;

	UPROPERTY(VisibleAnywhere, Category = "Tile")
	int32 TileGridY = 0;

	UPROPERTY(VisibleAnywhere, Category = "Tile")
	TObjectPtr<ALandscape> Landscape = nullptr;
};

/**
 * Editor-only configuration object for the Mapbox Landscape Importer.
 * Lives in UMapboxImporterEditorSubsystem; the SMapboxImporterPanel binds an IDetailsView to it.
 * Not an actor — strictly an authoring tool that exists only at edit-time.
 */
UCLASS(BlueprintType, NotBlueprintable)
class MAPBOXLANDSCAPE_API UMapboxImporterConfig : public UObject
{
	GENERATED_BODY()

public:
	UMapboxImporterConfig();

	/** Returns the editor world; the fetch spawns ALandscape actors into it. */
	virtual UWorld* GetWorld() const override;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Placement", meta = (ToolTip = "World-space origin used to anchor spawned landscape tiles. Move it to relocate the import area; you can also move the spawned ALandscape actors directly afterward."))
	FVector ImportOrigin = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates")
	ECoordinateMode CoordinateMode = ECoordinateMode::CenterRadius;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides))
	double North = 36.17;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides))
	double South = 36.15;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides))
	double East = -86.77;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides))
	double West = -86.79;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius", EditConditionHides))
	double CenterLatitude = -1.2921;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius", EditConditionHides))
	double CenterLongitude = 36.8219;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius", EditConditionHides, ClampMin = "0.1", ClampMax = "200.0"))
	double RadiusKm = 5.0;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::ToolString", EditConditionHides))
	FString CoordinateString;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling")
	bool bAutoZoom = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (EditCondition = "!bAutoZoom", ClampMin = "8", ClampMax = "18"))
	int32 ZoomLevel = 14;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ClampMin = "1", ClampMax = "16", ToolTip = "Web-mercator tiles grouped together into one ALandscape. 4 -> 1024px landscapes. Lower = more landscapes, higher fidelity per actor."))
	int32 TilesPerLandscapeSide = 4;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ClampMin = "1", ClampMax = "256", ToolTip = "Hard cap so a typo doesn't request thousands of tiles."))
	int32 MaxLandscapesTotal = 64;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling")
	int32 MaxConcurrentRequests = 16;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ClampMin = "1.0", ClampMax = "1000.0", ToolTip = "Cell size in cm per heightmap sample. 100 = 1m per pixel."))
	float MetersPerPixel = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Elevation", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float ZExaggeration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Elevation")
	bool bRebaseToSeaLevel = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Satellite")
	EMapboxSatelliteMode SatelliteMode = EMapboxSatelliteMode::BlendIntoMaterial;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Style", meta = (ToolTip = "Mapbox style used to derive the layer classification. Pick a style with solid colors per land type."))
	FString MetadataStyleId = TEXT("mapbox/satellite-streets-v12");

	UPROPERTY(EditAnywhere, Category = "Mapbox|Layers")
	TArray<FMapboxLayerDef> MapboxLayers;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Material", meta = (ToolTip = "Master landscape material. Leave empty to auto-generate the default M_MapboxLandscape on Fetch."))
	TSoftObjectPtr<UMaterialInterface> LandscapeMasterMaterial;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Material")
	bool bAutoGenerateDefaultAssets = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|PCG", meta = (ToolTip = "PCG graph spawned on each landscape to scatter the per-layer assets. Auto-generated if empty."))
	TSoftObjectPtr<UPCGGraphInterface> ScatterPCGGraph;

	UPROPERTY(EditAnywhere, Category = "Mapbox|PCG")
	bool bSpawnPCGComponents = true;

	UPROPERTY(VisibleAnywhere, Category = "Mapbox|Status")
	TArray<FMapboxTileResult> GeneratedLandscapes;

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions")
	void FetchLandscape();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions")
	void ClearGeneratedLandscapes();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions")
	void ResetLayersToDefaults();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Force regeneration of the default M_MapboxLandscape material and PCG scatter graph in the plugin's Content folder."))
	void RegenerateDefaultAssets();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Copy the current project settings (zoom, layers, material, etc.) into this importer."))
	void ResetFromProjectSettings();

	static FString GetApiKey();

	struct FTileCoord { int32 X = 0; int32 Y = 0; int32 Z = 0; };
	enum class ETileKind : uint8 { Height, Metadata, Satellite };

protected:
#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* InProperty) const override;
#endif

private:
	struct FTileBlob
	{
		FTileCoord Coord;
		ETileKind Kind;
		TArray<uint8> Bytes;
		bool bOk = false;
	};

	struct FLandscapeChunk
	{
		int32 ChunkX = 0;
		int32 ChunkY = 0;
		int32 MinTileX = 0;
		int32 MinTileY = 0;
		int32 TilesX = 0;
		int32 TilesY = 0;
	};

	void ResolveBoundingBox(double& OutNorth, double& OutSouth, double& OutEast, double& OutWest) const;
	int32 PickAutoZoom(double DegreesPerSide) const;
	void EnumerateTiles(double N, double S, double E, double W, int32 Zoom);
	void StartNextDownloads();
	void StartRequest(const FTileCoord& Coord, ETileKind Kind);
	void OnTileResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FTileCoord Coord, ETileKind Kind);
	void OnAllTilesDownloaded();

	uint16 DecodeHeight(uint8 R, uint8 G, uint8 B) const;
	int32 ClassifyPixel(const FColor& Pixel) const;

	UTexture2D* SaveTransientToAsset(const TArray<FColor>& Pixels, int32 W, int32 H, const FString& AssetName) const;
	UMaterialInterface* GetOrGenerateMasterMaterial();
	UPCGGraphInterface* GetOrGenerateScatterGraph();

	ALandscape* SpawnLandscapeForChunk(const FLandscapeChunk& Chunk,
	                                   const TArray<uint16>& HeightData,
	                                   const TMap<FName, TArray<uint8>>& LayerWeights,
	                                   UTexture2D* SatelliteTexture,
	                                   double LandscapeVertsPerSide,
	                                   double WorldSizePerLandscapeCm,
	                                   double LandscapeZScale,
	                                   double TileWorldCm,
	                                   double TotalWorldX,
	                                   double TotalWorldY);

	void SpawnPCGForLandscape(ALandscape* Landscape, UTexture2D* SatelliteTexture,
	                          const TMap<FName, TArray<uint8>>& LayerWeights,
	                          int32 LandscapeVerts,
	                          double WorldSizePerLandscapeCm);

	void SpawnSatelliteDecal(ALandscape* Landscape, UTexture2D* SatelliteTexture,
	                         double WorldSizePerLandscapeCm);

	void EnsureDefaultLayers();
	void FinishFetch();

	TArray<FTileCoord> PendingDownloadQueue;
	TMap<FString, FTileBlob> CompletedBlobs;
	TArray<FLandscapeChunk> Chunks;
	int32 InFlightRequests = 0;
	int32 TotalExpectedBlobs = 0;
	int32 ResolvedZoom = 14;

	int32 MinTileX = 0;
	int32 MaxTileX = 0;
	int32 MinTileY = 0;
	int32 MaxTileY = 0;

	bool bIsFetching = false;
};
