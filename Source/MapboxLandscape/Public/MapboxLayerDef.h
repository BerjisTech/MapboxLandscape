#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "MapboxLayerDef.generated.h"

UENUM(BlueprintType)
enum class EMapboxColorSpace : uint8
{
	RGB UMETA(DisplayName = "RGB (linear distance)"),
	HSV UMETA(DisplayName = "HSV (hue-aware, recommended for natural colors)")
};

UENUM(BlueprintType)
enum class EMapboxSatelliteMode : uint8
{
	None UMETA(DisplayName = "None"),
	BlendIntoMaterial UMETA(DisplayName = "Blend Into Landscape Material"),
	OverlayDecal UMETA(DisplayName = "Project As Decal Above Landscape")
};

UENUM(BlueprintType)
enum class EMapboxLayerMatchMode : uint8
{
	Color UMETA(DisplayName = "Color (raster style tile)"),
	Vector UMETA(DisplayName = "Vector Feature (MVT tile)"),
	Both UMETA(DisplayName = "Either Color OR Vector")
};

/**
 * One vector match rule. Combined with EMapboxLayerMatchMode = Vector or Both, this lets a layer
 * pull data from Mapbox Streets v8 vector tiles. Each layer may have multiple filters (e.g. a single
 * "Roads" layer matching both road/motorway and road/trunk).
 */
USTRUCT(BlueprintType)
struct FMapboxVectorFeatureFilter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector Filter", meta = (ToolTip = "Mapbox Streets v8 layer name. Common values: 'road' (all roads/rails), 'water' (water polygons), 'building' (building polygons), 'landuse' (parks/forest/industrial/etc.), 'aeroway' (runways/taxiways), 'landuse_overlay' (national parks/wetland)."))
	FString MvtLayer = TEXT("road");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector Filter", meta = (ToolTip = "Optional: restrict to features whose 'class' property is one of these. Empty array = match every feature in MvtLayer. Examples: ['motorway','trunk'] for highways; ['major_rail','minor_rail'] for railways; ['runway'] for airports; ['wood','forest'] for landuse forest."))
	TArray<FString> Classes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector Filter", meta = (ClampMin = "0.5", ToolTip = "Stroke width in meters when rasterizing LineString features (roads, rails, runways). Ignored for polygon features (buildings, water, landuse). Realistic: motorway=15, primary=10, residential=6, path=2, rail=4, runway=45."))
	float LineWidthMeters = 5.f;
};

USTRUCT(BlueprintType)
struct FMapboxLayerDef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layer", meta = (ToolTip = "Display name and landscape weight-map key. Becomes the FName used by the landscape's blend material."))
	FName LayerName = TEXT("NewLayer");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layer", meta = (ToolTip = "How this layer decides whether a pixel belongs to it.\n- Color: matches a raster style tile by HSV/RGB distance (catches landuse painted on the map but not road classes).\n- Vector: matches semantic Mapbox features (motorway, railway, building, water polygon, etc.) — much more precise.\n- Both: pixel matches if EITHER color OR vector says so."))
	EMapboxLayerMatchMode MatchMode = EMapboxLayerMatchMode::Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layer", meta = (ClampMin = "0", ClampMax = "100", ToolTip = "Higher priority overrides lower priority when the same pixel matches multiple layers. Roads (40-50) should be above grass (10); buildings/water (60-70) should be above roads. Highest wins."))
	int32 Priority = 0;

	// ---- Color matching ----

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (EditCondition = "MatchMode != EMapboxLayerMatchMode::Vector", EditConditionHides, ToolTip = "Target RGB color to match in the raster style tile. Use HSV space below to handle natural variation."))
	FLinearColor TargetColor = FLinearColor(0.3f, 0.6f, 0.2f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (EditCondition = "MatchMode != EMapboxLayerMatchMode::Vector", EditConditionHides, ToolTip = "HSV is hue-aware (good for vegetation/water with brightness variation). RGB uses Euclidean distance (good for paint-like colors)."))
	EMapboxColorSpace ColorSpace = EMapboxColorSpace::HSV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "MatchMode != EMapboxLayerMatchMode::Vector && ColorSpace == EMapboxColorSpace::HSV", EditConditionHides))
	float HueTolerance = 0.08f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "MatchMode != EMapboxLayerMatchMode::Vector && ColorSpace == EMapboxColorSpace::HSV", EditConditionHides))
	float SatTolerance = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "MatchMode != EMapboxLayerMatchMode::Vector && ColorSpace == EMapboxColorSpace::HSV", EditConditionHides))
	float ValTolerance = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "MatchMode != EMapboxLayerMatchMode::Vector && ColorSpace == EMapboxColorSpace::RGB", EditConditionHides))
	float RGBTolerance = 0.2f;

	// ---- Vector matching ----

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector Match", meta = (EditCondition = "MatchMode != EMapboxLayerMatchMode::Color", EditConditionHides, ToolTip = "One or more rules describing which Mapbox vector features belong to this layer. ANY rule matching includes the feature."))
	TArray<FMapboxVectorFeatureFilter> VectorFilters;

	// ---- Material ----

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (ToolTip = "Tint passed to the landscape material as <LayerName>_Tint parameter. The auto-generated M_MapboxLandscape doesn't currently use per-layer tints, but a user-supplied master material can."))
	FLinearColor MaterialTint = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TSoftObjectPtr<UTexture2D> AlbedoTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (ToolTip = "Physical material applied where this layer's weight is dominant (controls footstep sounds, vehicle friction, etc.)"))
	TSoftObjectPtr<UPhysicalMaterial> PhysicalMaterial;

	// ---- Scatter ----

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (ToolTip = "If on, the plugin scatters static meshes from ScatterMeshes onto this layer's pixels (via HISM components or PCG)."))
	bool bScatterEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ToolTip = "Static meshes spawned on this layer. The plugin picks one at random per instance — fill with several variants for natural variety."))
	TArray<TSoftObjectPtr<UStaticMesh>> ScatterMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "0.0", ToolTip = "Average meshes per 100 square meters. 4 = ~1 tree per 25m^2 (sparse forest). 12 = dense grass. 0.5 = scattered landmarks."))
	float ScatterDensity = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "0.5", ToolTip = "Minimum world-space spacing between scatter instances, meters. Floor on stride so dense layers (grass) don't spawn millions of instances when landscape resolution is high. 3m = grass density, 8m = trees."))
	float ScatterMinSpacingMeters = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "100", ClampMax = "1000000", ToolTip = "Hard cap on instances spawned per layer per landscape. Safety belt: if ScatterDensity + tile size would produce more, the scatter loop bails after this many. Tune up if you want denser foliage and have GPU headroom."))
	int32 ScatterMaxInstancesPerLandscape = 50000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "0.0", ToolTip = "Each instance is randomly scaled in [Min, Max]. 0.8/1.3 = mild natural variation."))
	float ScatterMinScale = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "0.0"))
	float ScatterMaxScale = 1.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ToolTip = "If on, each instance is rotated to a random yaw [0, 360]. Off = all instances face +X (use this for vehicles, aligned crops, etc.)"))
	bool bRandomYaw = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ToolTip = "If on, instance Z is aligned with the landscape surface normal (steep slopes will tilt instances). Off = instances stand vertically regardless of slope."))
	bool bAlignToLandscapeNormal = false;
};

/**
 * Per-road-class visual settings for the World Features generator. Each entry describes one class
 * of OpenStreetMap road (e.g. motorway, primary, residential, path, rail) and how the plugin should
 * render it on the landscape: which static mesh to sweep along the spline, which landscape paint
 * layer to apply for road-shoulder color (e.g. Sand for Brushify-style dust), and how wide to make
 * the spline mesh + paint deformation.
 *
 * Maps to Epic's built-in ULandscapeSplineSegment system — the engine handles mesh tiling and
 * landscape paint deformation; we just feed it the polyline geometry and the per-segment specs.
 */
USTRUCT(BlueprintType)
struct FMapboxRoadClassSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ToolTip = "Display name. Doesn't affect generation — just helps you find this entry in the array."))
	FName ClassName = TEXT("Residential");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ToolTip = "If off, this class is skipped. Useful for testing one class at a time without deleting the others."))
	bool bEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ToolTip = "Mapbox Streets v8 layer to read from. 'road' for streets/paths/rails. Default is 'road' and you rarely need anything else."))
	FString MvtLayer = TEXT("road");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ToolTip = "Match features whose 'class' property is one of these. Examples:\n  ['motorway']                    — interstates/freeways\n  ['primary', 'trunk']            — major roads\n  ['secondary', 'tertiary']       — regional\n  ['residential', 'service']      — neighborhood streets\n  ['path', 'pedestrian', 'track'] — footpaths\n  ['major_rail', 'minor_rail']    — railways"))
	TArray<FString> MvtClassMatches;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ToolTip = "Spline mesh swept along the road. Should be aligned so its local +X axis is the forward direction. Compatible with Brushify road kits, Epic's spline road meshes, or any single-axis mesh. Leave empty to skip mesh generation (paint layer still applies)."))
	TSoftObjectPtr<UStaticMesh> SplineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ClampMin = "0.5", ToolTip = "Spline mesh width in meters. Should match the visual width of your road mesh — too narrow and it stretches; too wide and it tiles oddly. Defaults: motorway=18, primary=12, residential=7, path=2, rail=4."))
	float SplineWidthMeters = 7.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ToolTip = "Landscape weight layer to paint along this road. e.g. 'Sand' for Brushify-style sandy shoulders, 'Dirt' for a country road look, or NAME_None to leave the underlying landscape paint untouched. The layer must already exist in the MapboxLayers config (i.e., your landscape must have been imported with that layer enabled)."))
	FName PaintLayer = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ClampMin = "0.5", ToolTip = "Paint deformation width in meters — how wide the landscape paint layer extends from the spline centerline. Usually a bit wider than SplineWidthMeters so the paint overlaps the road shoulder. Set to 0 to disable paint deformation."))
	float PaintWidthMeters = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ClampMin = "0.0", ToolTip = "Lift the road this many cm above the landscape surface. Helps prevent z-fighting where the road mesh meets the terrain. 5–10 cm is usually enough."))
	float RaiseAboveTerrainCm = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Class", meta = (ClampMin = "1.0", ToolTip = "Distance in meters between spline control points along the road. Smaller = smoother curves but more control points (heavier landscape). 20 m is fine for most roads; 5 m for tight mountain switchbacks."))
	float ControlPointSpacingMeters = 20.0f;
};
