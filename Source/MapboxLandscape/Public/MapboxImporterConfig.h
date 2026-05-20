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
 * Not an actor - strictly an authoring tool that exists only at edit-time.
 */
UCLASS(BlueprintType, NotBlueprintable)
class MAPBOXLANDSCAPE_API UMapboxImporterConfig : public UObject
{
	GENERATED_BODY()

public:
	UMapboxImporterConfig();

	/** Returns the editor world; the fetch spawns ALandscape actors into it. */
	virtual UWorld* GetWorld() const override;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Placement", meta = (ToolTip = "World-space origin used to anchor the imported landscape grid (in centimeters, UE world units). (0,0,0) is the level origin. After fetch you can also move each spawned ALandscape actor individually in the World Outliner. Z is added to every landscape on top of its terrain height - useful if your level uses a non-zero ground plane."))
	FVector ImportOrigin = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (ToolTip = "How you want to describe the area to import. Center Point & Radius is the easiest: drop a lat/lng plus a radius and the plugin computes the bounds. Bounding Box if you need an exact N/S/E/W rectangle. Tool String if you have a comma-separated list of coordinates from bbox-finder/blender-osm."))
	ECoordinateMode CoordinateMode = ECoordinateMode::CenterRadius;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides, ToolTip = "Northern (max) latitude of the import rectangle in decimal degrees (e.g. 36.17)."))
	double North = 36.17;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides, ToolTip = "Southern (min) latitude of the import rectangle in decimal degrees."))
	double South = 36.15;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides, ToolTip = "Eastern (max) longitude of the import rectangle in decimal degrees (negative = western hemisphere)."))
	double East = -86.77;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::BoundingBox", EditConditionHides, ToolTip = "Western (min) longitude of the import rectangle in decimal degrees."))
	double West = -86.79;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius", EditConditionHides, ToolTip = "Latitude of the import center, decimal degrees. Tip: pick on Google Maps, right-click, copy coordinates."))
	double CenterLatitude = -1.2921;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius", EditConditionHides, ToolTip = "Longitude of the import center, decimal degrees."))
	double CenterLongitude = 36.8219;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::CenterRadius", EditConditionHides, ClampMin = "0.1", ClampMax = "200.0", ToolTip = "Half-side length of the square area to import, in kilometers. Radius 5 = 10x10 km area. Larger areas cost more API requests and produce more landscape tiles."))
	double RadiusKm = 5.0;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Coordinates", meta = (EditCondition = "CoordinateMode == ECoordinateMode::ToolString", EditConditionHides, ToolTip = "Comma- or space-separated list of lat/lng pairs. Plugin auto-detects order (lat,lng vs lng,lat) and uses the min/max as the bounding rectangle."))
	FString CoordinateString;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ToolTip = "If on, the plugin picks the best Mapbox zoom level for your area automatically (higher zoom = more detail, more tiles). Turn off to force a specific zoom via the Zoom Level field below."))
	bool bAutoZoom = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (EditCondition = "!bAutoZoom", ClampMin = "8", ClampMax = "18", ToolTip = "Mapbox web-mercator zoom level (the 'z' in z/x/y tile URLs). 10 ~ city region (~10km per tile). 12 ~ neighborhood (~2km per tile). 14 ~ street level (~600m per tile) - good default. 16 ~ building level (~150m per tile). 18 ~ maximum detail (~40m per tile). Each step up = 4x more tiles to fetch."))
	int32 ZoomLevel = 14;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ClampMin = "1", ClampMax = "16", ToolTip = "How many Mapbox tiles get baked into ONE ALandscape actor (NxN). 1 = each tile becomes its own landscape (lots of small landscapes, most flexible). 4 = each landscape holds 16 tiles (4x4) - good default. 8+ = fewer, larger landscapes (faster to traverse, more memory per actor)."))
	int32 TilesPerLandscapeSide = 4;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ClampMin = "1", ClampMax = "256", ToolTip = "Safety cap on how many ALandscape actors the import is allowed to spawn. If your radius + zoom would exceed this, the fetch aborts with an error so a typo doesn't request thousands of tiles."))
	int32 MaxLandscapesTotal = 64;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ToolTip = "How many tile HTTP requests run in parallel. Higher = faster fetch but more likely to hit Mapbox rate limits (which return HTTP 429). 16 is safe."))
	int32 MaxConcurrentRequests = 16;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (ClampMin = "1.0", ClampMax = "1000.0", ToolTip = "Reserved for future use. Current pipeline derives world spacing from the tile geometry directly."))
	float MetersPerPixel = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Elevation", meta = (ClampMin = "0.1", ClampMax = "10.0", ToolTip = "Multiplier applied to real-world elevation to exaggerate or flatten the terrain. 1.0 = real-world (a 100m hill is 100m tall in-game). 2.0 = doubled (mountains look more dramatic). 0.5 = halved (gentler hills). Tweak after import to dial in the feel."))
	float ZExaggeration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Elevation", meta = (ToolTip = "If on, the lowest sampled point in the import becomes world Z=0 and everything else is relative to it. Useful when the imported area is far above sea level (e.g. Nairobi at ~1800m) and you don't want the whole map floating high. If off, real altitudes are used (the surface sits at its actual world Z elevation)."))
	bool bRebaseToSeaLevel = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Satellite", meta = (ToolTip = "How to apply the Mapbox satellite imagery. None = no satellite (you'll author the material yourself). Blend Into Material = bake the satellite texture into a per-landscape material instance, applied directly. Cheapest, best for distant views. Overlay Decal = spawn a decal actor that projects the satellite imagery onto the terrain from above. Lets you keep a separate base material and still see roads/buildings from satellite."))
	EMapboxSatelliteMode SatelliteMode = EMapboxSatelliteMode::BlendIntoMaterial;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Style", meta = (ToolTip = "Mapbox style used to derive the per-pixel land classification (urban/forest/water/etc.) from raster tiles. Pick a style with solid, distinct colors for different land use. Defaults to mapbox/satellite-streets-v12 which mixes satellite imagery with road overlays. Custom styles you've authored in Mapbox Studio work here too (format: username/style-id)."))
	FString MetadataStyleId = TEXT("mapbox/satellite-streets-v12");

	UPROPERTY(EditAnywhere, Category = "Mapbox|Layers", meta = (ToolTip = "Defines how pixel colors in the metadata style tile map to landscape layers (Forest, Urban, Water, etc). Each entry has a target color, tolerance, priority, and an optional array of static meshes that get scattered on that layer. Use 'Reset Layers To Defaults' to restore a sensible starting set."))
	TArray<FMapboxLayerDef> MapboxLayers;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Material", meta = (ToolTip = "Master landscape material every imported landscape uses as parent. Leave EMPTY to have the plugin auto-generate M_MapboxLandscape on first fetch (parameter 'SatelliteTexture' plus roughness). Override with your own material if you want custom blending, normal maps, or grass shaders - just expose a 'SatelliteTexture' parameter so the plugin can inject the per-chunk imagery."))
	TSoftObjectPtr<UMaterialInterface> LandscapeMasterMaterial;

	UPROPERTY(EditAnywhere, Category = "Mapbox|Material", meta = (ToolTip = "If on, missing default assets (master material, decal material, PCG graph) are auto-created in /Game/MapboxLandscape/ on first fetch. Turn off if you only want to use your own assets and never the auto-generated ones."))
	bool bAutoGenerateDefaultAssets = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|PCG", meta = (ToolTip = "PCG graph that runs on each spawned landscape to scatter the per-layer meshes (trees, grass, etc.). Leave empty to use the plugin's HISM-based fallback scatter (deterministic grid sampling respecting layer weights - works without PCG)."))
	TSoftObjectPtr<UPCGGraphInterface> ScatterPCGGraph;

	UPROPERTY(EditAnywhere, Category = "Mapbox|PCG", meta = (ToolTip = "If on, a UPCGComponent is added to each landscape that runs the ScatterPCGGraph above. Independent of the HISM fallback scatter - both can run."))
	bool bSpawnPCGComponents = true;

	UPROPERTY(VisibleAnywhere, Category = "Mapbox|Status", meta = (ToolTip = "References to the ALandscape actors created by the most recent Fetch. Read-only - use Clear Generated Landscapes to remove them."))
	TArray<FMapboxTileResult> GeneratedLandscapes;

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Downloads all Mapbox tiles for the configured area and spawns ALandscape actors into the active level. Watch the bottom-right toasts for progress."))
	void FetchLandscape();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Destroys every landscape actor created by the most recent Fetch. Other landscapes in your level are left alone."))
	void ClearGeneratedLandscapes();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Restores the default layer set (Forest / Grass / Urban / Road / Water) with sensible color matches. Your custom mesh assignments are wiped."))
	void ResetLayersToDefaults();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Force-recreates the default M_MapboxLandscape master material, decal material, and PCG scatter graph in /Game/MapboxLandscape/. Use this if you accidentally deleted them."))
	void RegenerateDefaultAssets();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Rebuilds the master material with the latest UV graph and updates every landscape's per-chunk material instance with current LandscapeOrigin / LandscapeWorldSize parameters. Use this if satellite textures are tiling/repeating across each landscape. No re-fetch needed."))
	void FixExistingLandscapeMaterials();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Copies the current Project Settings > Plugins > Mapbox Landscape defaults (zoom, layers, material, etc.) into this importer, overwriting your in-panel edits."))
	void ResetFromProjectSettings();

	static FString GetApiKey();

	struct FTileCoord { int32 X = 0; int32 Y = 0; int32 Z = 0; };
	enum class ETileKind : uint8 { Height, Metadata, Satellite, Vector };

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
	class UMaterialInstanceConstant* CreateMaterialInstanceForChunk(UMaterialInterface* Master, UTexture2D* SatelliteTexture,
		int32 ChunkX, int32 ChunkY, FVector LandscapeOriginCm, double LandscapeWorldSizeCm) const;
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
