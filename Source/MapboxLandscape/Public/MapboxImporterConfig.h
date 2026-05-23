#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Interfaces/IHttpRequest.h"
#include "Materials/MaterialInterface.h"
#include "MapboxLayerDef.h"
#include "MapboxImporterConfig.generated.h"

class UPCGGraphInterface;
class ALandscape;
class ALandscapeProxy;
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
	TObjectPtr<ALandscapeProxy> Landscape = nullptr;
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

	UPROPERTY(EditAnywhere, Category = "Mapbox|Tiling", meta = (EditCondition = "!bAutoZoom", ClampMin = "8", ClampMax = "15", ToolTip = "Mapbox web-mercator zoom level (the 'z' in z/x/y tile URLs). 10 ~ city region (~10km per tile). 12 ~ neighborhood (~2km per tile). 14 ~ street level (~600m per tile) - good default. 15 ~ block level (~300m per tile). Capped at 15 because that's the highest zoom Mapbox's terrain-RGB tiles serve - going higher would produce a flat landscape because all height tiles would return 404."))
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

	UPROPERTY(EditAnywhere, Category = "Mapbox|Elevation", meta = (ClampMin = "0", ClampMax = "2", ToolTip = "Fetch height tiles at zoom+N above the satellite/style zoom for sharper terrain detail and smoother cliff edges. +1 quadruples height-tile count but produces ~2x denser elevation samples per landscape vertex (good for sharp escarpments / small areas). +2 is 16x more height tiles - only use for small areas <5km. 0 (default) keeps height at the same zoom and is the right choice for medium-to-large fetches."))
	int32 HeightZoomBonus = 0;

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

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features", meta = (ToolTip = "Tick to include road/path/railway splines when you run 'Populate World Features'. Doesn't affect Fetch Landscape — world features are now a separate populate step that runs against existing Mapbox-fetched landscapes."))
	bool bPopulateRoads = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features", meta = (EditCondition = "bPopulateRoads", ToolTip = "Per-OSM-road-class mesh and paint settings. Order doesn't matter — each road feature is matched against every entry's class list. Use 'Reset Road Classes To Defaults' to populate a sensible starting set covering motorway, primary, secondary, tertiary, residential, path, and rail."))
	TArray<FMapboxRoadClassSettings> RoadClasses;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features", meta = (ToolTip = "If on, the editor's small mountain-shaped sprite icons that mark every landscape spline control point get hidden after population. Highly recommended — a city's worth of icons tile-fills the viewport and crushes editor performance. You can still edit splines via Landscape Mode > Spline; the icons aren't needed for selection."))
	bool bHideSplineEditorSprites = true;

	// --- Water bodies ---
	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Water", meta = (ToolTip = "Tick to generate flat water-plane meshes from Mapbox `water` polygons (lakes, rivers, coast) when you run Populate World Features. One UProceduralMeshComponent per polygon, attached to the matching landscape actor."))
	bool bPopulateWater = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Water", meta = (EditCondition = "bPopulateWater", ToolTip = "Material applied to every water plane. Should be translucent / use the engine's water shading. Leave empty to use the engine default material (unlit grey) — fine for a flat-shaded preview, ugly for a final render. Tip: assign Water/M_Water_LakeRiver from the Water plugin's content if installed."))
	TSoftObjectPtr<class UMaterialInterface> WaterMaterial;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Water", meta = (EditCondition = "bPopulateWater", ClampMin = "-1000", ClampMax = "1000", ToolTip = "Vertical offset applied to every water plane, in cm. Mapbox `water` polygons have no Z attribute, so we place them at the average landscape Z under the polygon and then offset by this amount. Slight negative (-50 cm) is usually best so the plane sinks below shoreline pixels and looks contained."))
	float WaterPlaneZOffsetCm = -50.f;

	// --- Buildings ---
	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Buildings", meta = (ToolTip = "Tick to generate extruded building meshes from Mapbox `building` polygons. Each polygon becomes a UProceduralMeshComponent with footprint walls + a flat roof. Footprint comes from the geometry; height comes from the MVT `height` property (or `min_height` for tower-on-podium), with a fallback when the property is missing."))
	bool bPopulateBuildings = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Buildings", meta = (EditCondition = "bPopulateBuildings", ClampMin = "1", ClampMax = "200", ToolTip = "Fallback height (m) used when a `building` feature has no `height` property — common for rural OSM data and any tile-set that doesn't expose 3-D building data. Realistic city default: 8 m (~2 storeys)."))
	float DefaultBuildingHeightMeters = 8.f;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Buildings", meta = (EditCondition = "bPopulateBuildings", ClampMin = "0.1", ClampMax = "5.0", ToolTip = "Multiplier on every building's height (real or fallback). Useful for stylisation or to compensate for tile-sets that underreport storey height. 1.0 = trust the data."))
	float BuildingHeightMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Buildings", meta = (EditCondition = "bPopulateBuildings", ToolTip = "Material applied to every generated building. Set to a tile-able wall material for best results; leaving empty uses the engine default (unlit grey). Roof and walls share this material — assignable separately later if needed."))
	TSoftObjectPtr<class UMaterialInterface> BuildingMaterial;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Features|Buildings", meta = (EditCondition = "bPopulateBuildings", ClampMin = "5", ClampMax = "10000", ToolTip = "Skip any building whose footprint is smaller than this in square meters. OSM data has lots of garden-shed-sized noise polygons that aren't worth meshing. 25 m² (a small kiosk) is a reasonable filter."))
	float MinBuildingFootprintSquareMeters = 25.f;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Partition", meta = (ToolTip = "If on AND the current level is World Partition, automatically convert imported chunks into spatially-loaded streaming proxies at the end of fetch (same op as Build > World Partition > Convert Landscape, just chained). WP then unloads distant proxies for low resident memory. Costs significant fetch time because each component gets its heightmap split into a per-component texture. Turn off if you want a fast fetch and will run the manual Convert Generated Landscapes To Streaming action later (or don't need streaming)."))
	bool bConvertToWorldPartitionStreaming = true;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Partition", meta = (ClampMin = "1", ClampMax = "32", EditCondition = "bConvertToWorldPartitionStreaming", ToolTip = "Components per WP grid cell during conversion. Smaller = finer streaming granularity (more proxies, more spawn cost, smaller load/unload steps). Larger = coarser streaming (fewer proxies, faster conversion, larger units). 16 matches our default per-chunk component count so each chunk becomes 1 proxy."))
	int32 WorldPartitionGridSizeInComponents = 16;

	UPROPERTY(EditAnywhere, Category = "Mapbox|World Partition", meta = (ClampMin = "1", ClampMax = "64", EditCondition = "bConvertToWorldPartitionStreaming", ToolTip = "How many landscapes to partition before flushing the texture compile queue. Smaller = lower peak memory during conversion, slower overall. Larger = faster, but the BC7 compile queue can pile up and trigger OS memory pressure near the end. 8 keeps the queue bounded on a 32 GB / 14 GB-free system."))
	int32 PartitionBatchSize = 8;

	UPROPERTY(VisibleAnywhere, Category = "Mapbox|Status", meta = (ToolTip = "References to the ALandscape actors created by the most recent Fetch. Read-only - use Clear Generated Landscapes to remove them."))
	TArray<FMapboxTileResult> GeneratedLandscapes;

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Downloads all Mapbox tiles for the configured area and spawns ALandscape actors into the active level. Watch the bottom-right toasts for progress."))
	void FetchLandscape();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Destroys every landscape actor created by the most recent Fetch. Other landscapes in your level are left alone."))
	void ClearGeneratedLandscapes();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Cancels a running fetch. In-flight HTTP requests can't be recalled, but no more landscapes will be processed after the current tile finishes. Use this when you accidentally requested too large an area."))
	void CancelFetch();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Restores the default layer set (Forest / Grass / Urban / Road / Water) with sensible color matches. Your custom mesh assignments are wiped."))
	void ResetLayersToDefaults();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Force-recreates the default M_MapboxLandscape master material, decal material, and PCG scatter graph in /Game/MapboxLandscape/. Use this if you accidentally deleted them."))
	void RegenerateDefaultAssets();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Rebuilds the master material with the latest UV graph and updates every landscape's per-chunk material instance with current LandscapeOrigin / LandscapeWorldSize parameters. Use this if satellite textures are tiling/repeating across each landscape. No re-fetch needed."))
	void FixExistingLandscapeMaterials();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Copies the current Project Settings > Plugins > Mapbox Landscape defaults (zoom, layers, material, etc.) into this importer, overwriting your in-panel edits."))
	void ResetFromProjectSettings();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Manually convert all Mapbox-generated landscapes in the level to World Partition streaming proxies. Equivalent to the auto-conversion at end of fetch, but you can run it any time — useful if you turned off Convert To World Partition Streaming on the original fetch, or want to re-convert after editing. Requires a World Partition level."))
	void ConvertGeneratedLandscapesToStreaming();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Populate Road Classes with a sensible default set: motorway, primary, secondary, tertiary, residential, path, rail. Your custom mesh + layer assignments are wiped — only the OSM-class-to-row mapping is reset."))
	void ResetRoadClassesToDefaults();

	UFUNCTION(CallInEditor, Category = "Mapbox|Actions", meta = (ToolTip = "Generate world features (roads, eventually buildings/water/vegetation) on top of existing Mapbox-fetched landscapes. Re-uses the current Lat/Lng/Radius/Zoom to know which Mapbox tiles to re-download, then drops the resulting polyline/polygon geometry onto each landscape actor it finds. Only the feature types ticked above are populated. Requires that a Fetch Landscape has already run (the plugin looks for MapboxLandscape_* actors in the level)."))
	void PopulateWorldFeatures();

	static FString GetApiKey();

	struct FTileCoord { int32 X = 0; int32 Y = 0; int32 Z = 0; };
	enum class ETileKind : uint8 { Height, Metadata, Satellite, Vector };

	/** Which pipeline the active fetch is running. Set on the actions' entry point; consumed by
	 *  StartNextDownloads (gates which tile kinds get requested) and OnAllTilesDownloaded (branches
	 *  to the matching processor). Reset to Landscape in FinishFetch. */
	enum class EFetchMode : uint8 { Landscape, WorldFeatures };

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
	void ProcessWorldFeaturesDownloaded();

	uint16 DecodeHeight(uint8 R, uint8 G, uint8 B) const;
	int32 ClassifyPixel(const FColor& Pixel) const;

	UTexture2D* SaveTransientToAsset(const TArray<FColor>& Pixels, int32 W, int32 H, const FString& AssetName) const;

	/** Returns the current editor level's short name (e.g. "Kisumu_Map"). Falls back to "Default"
	 *  when no level is loaded or the level is unsaved. Used to segregate per-fetch assets by level. */
	FString GetLevelSubfolder() const;
	UMaterialInterface* GetOrGenerateMasterMaterial();
	class UMaterialInstanceConstant* CreateMaterialInstanceForChunk(UMaterialInterface* Master, UTexture2D* SatelliteTexture,
		int32 ChunkX, int32 ChunkY, FVector LandscapeOriginCm, double LandscapeWorldSizeCm) const;
	UPCGGraphInterface* GetOrGenerateScatterGraph();

	// Per-axis vertex counts and world sizes: trailing-edge chunks (east / south of the
	// import region) have TilesX != TilesY, so a single "per side" dim would either leave
	// gaps (too small in Y) or overlap neighbours (too large in X). See the chunk loop in
	// MapboxImporterConfig.cpp for the matching VertsX/VertsY/WorldSizeXCm/WorldSizeYCm
	// computation and docs/leakage-defense.md... oops, see the floating-tile fix commit
	// in this repo.
	ALandscapeProxy* SpawnLandscapeForChunk(const FLandscapeChunk& Chunk,
	                                        const TArray<uint16>& HeightData,
	                                        const TMap<FName, TArray<uint8>>& LayerWeights,
	                                        UTexture2D* SatelliteTexture,
	                                        double LandscapeVertsXPerSide,
	                                        double LandscapeVertsYPerSide,
	                                        double WorldSizeXCm,
	                                        double WorldSizeYCm,
	                                        double LandscapeZScale,
	                                        double TileWorldCm,
	                                        double TotalWorldX,
	                                        double TotalWorldY);

	void SpawnPCGForLandscape(ALandscapeProxy* Landscape, UTexture2D* SatelliteTexture,
	                          const TMap<FName, TArray<uint8>>& LayerWeights,
	                          const TArray<uint16>& Heightmap,
	                          int32 LandscapeVertsX,
	                          int32 LandscapeVertsY,
	                          double WorldSizeXCm,
	                          double WorldSizeYCm,
	                          double LandscapeZScale);

	void SpawnSatelliteDecal(ALandscapeProxy* Landscape, UTexture2D* SatelliteTexture,
	                         double WorldSizeXCm, double WorldSizeYCm);

	/** Internal: partition a single ALandscape into WP streaming proxies. Called by the public batch action;
	 *  not for direct use because it doesn't drain the texture compile queue. No-op outside a WP world. */
	void PartitionSingleLandscape(ALandscapeProxy* Landscape);

	/** One polyline collected from the MVT parse pass, ready for spline generation. Coords are in
	 *  landscape-pixel space (i.e. [0, LandscapeVerts]) so they share the same coordinate system as the
	 *  Heightmap array — saves us re-transforming during the vector-parse loop. */
	struct FCollectedRoadPolyline
	{
		int32 RoadClassIndex = INDEX_NONE;
		TArray<FVector2D> LandscapePixels;
	};

	/** Build ULandscapeSplineControlPoint + ULandscapeSplineSegment objects on the landscape's spline
	 *  component, one per collected polyline. Samples Z via a world-space line trace against the
	 *  landscape collision per control point (works during fetch + during post-hoc populate without
	 *  needing the heightmap in memory). No-op if Roads is empty or RoadClasses is empty. */
	void GenerateRoadSplinesForChunk(ALandscapeProxy* Landscape,
	                                 const TArray<FCollectedRoadPolyline>& Roads,
	                                 int32 LandscapeVerts,
	                                 double WorldSizePerLandscapeCm,
	                                 double LandscapeZScale,
	                                 const FVector& ChunkOrigin);

	/** One polygon collected from the MVT parse pass — either a water body or a building footprint.
	 *  Coords are in landscape-pixel space (same as FCollectedRoadPolyline). Rings holds one or more
	 *  rings per MVT feature; ring[0] is the outer, subsequent rings are holes. HeightMeters is the
	 *  feature's `height` property when present (buildings only); -1 means "use the fallback". */
	struct FCollectedPolygon
	{
		TArray<TArray<FVector2D>> Rings;
		float HeightMeters = -1.f;
		float MinHeightMeters = 0.f;
	};

	/** Build flat water-plane meshes via UProceduralMeshComponent, one component per polygon.
	 *  Triangulates the outer ring (holes ignored for v1 — Mapbox water polygons are rarely
	 *  multiring at the zooms we use), places at average terrain Z under the footprint + the
	 *  user's WaterPlaneZOffsetCm, applies WaterMaterial. */
	void GenerateWaterMeshesForChunk(ALandscapeProxy* Landscape,
	                                 const TArray<FCollectedPolygon>& Waters,
	                                 int32 LandscapeVerts,
	                                 double WorldSizePerLandscapeCm,
	                                 const FVector& ChunkOrigin);

	/** Build extruded building meshes via UProceduralMeshComponent, one component per polygon.
	 *  Triangulates the outer ring for the roof cap; emits quad walls from each footprint edge.
	 *  Footprint area-filter and height resolution (data → default → multiplier) happen here. */
	void GenerateBuildingMeshesForChunk(ALandscapeProxy* Landscape,
	                                    const TArray<FCollectedPolygon>& Buildings,
	                                    int32 LandscapeVerts,
	                                    double WorldSizePerLandscapeCm,
	                                    const FVector& ChunkOrigin);

	void EnsureDefaultLayers();
	void FinishFetch();

	TArray<FTileCoord> PendingDownloadQueue;
	TMap<FString, FTileBlob> CompletedBlobs;
	TArray<FLandscapeChunk> Chunks;
	int32 InFlightRequests = 0;
	int32 TotalExpectedBlobs = 0;
	int32 CompletedBlobCount = 0;       // for download progress logging/toasting
	int32 LastReportedProgressBlobs = 0; // last value at which we emitted a progress toast
	int32 FailedHeightBlobs = 0;        // count of height tiles that returned an error or empty body
	int32 ResolvedZoom = 14;

	int32 MinTileX = 0;
	int32 MaxTileX = 0;
	int32 MinTileY = 0;
	int32 MaxTileY = 0;

	bool bIsFetching = false;
	bool bCancelRequested = false;
	EFetchMode FetchMode = EFetchMode::Landscape;
};
