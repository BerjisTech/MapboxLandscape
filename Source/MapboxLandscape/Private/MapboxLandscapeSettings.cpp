#include "MapboxLandscapeSettings.h"

// Build the default layer set. Keep this in sync with EnsureDefaultLayers in MapboxImporterConfig.cpp -
// they describe the same authoring schema; project settings is just the persisted copy.
static FMapboxLayerDef MakeVectorLayer(FName Name, const FString& MvtLayer, const TArray<FString>& Classes,
	float LineWidth, int32 Priority, FLinearColor Tint, bool bScatter = false, float Density = 0.f, float MinSpacing = 3.f)
{
	FMapboxLayerDef L;
	L.LayerName = Name;
	L.MatchMode = EMapboxLayerMatchMode::Vector;
	L.Priority = Priority;
	L.MaterialTint = Tint;
	L.bScatterEnabled = bScatter;
	L.ScatterDensity = Density;
	L.ScatterMinSpacingMeters = MinSpacing;

	FMapboxVectorFeatureFilter F;
	F.MvtLayer = MvtLayer;
	F.Classes = Classes;
	F.LineWidthMeters = LineWidth;
	L.VectorFilters.Add(F);
	return L;
}

static FMapboxLayerDef MakeColorLayer(FName Name, FLinearColor Target, FLinearColor Tint, int32 Priority,
	float HueTol, float SatTol, float ValTol, bool bScatter = false, float Density = 0.f, float MinSpacing = 3.f)
{
	FMapboxLayerDef L;
	L.LayerName = Name;
	L.MatchMode = EMapboxLayerMatchMode::Color;
	L.TargetColor = Target;
	L.MaterialTint = Tint;
	L.Priority = Priority;
	L.ColorSpace = EMapboxColorSpace::HSV;
	L.HueTolerance = HueTol;
	L.SatTolerance = SatTol;
	L.ValTolerance = ValTol;
	L.bScatterEnabled = bScatter;
	L.ScatterDensity = Density;
	L.ScatterMinSpacingMeters = MinSpacing;
	return L;
}

UMapboxLandscapeSettings::UMapboxLandscapeSettings()
{
	if (DefaultLayers.IsEmpty())
	{
		// "Clear" - special layer. The importer recognizes the literal name "Clear" and uses its weight
		// to flatten the heightmap to baseline and zero the material opacity (carves holes / hills out).
		FMapboxLayerDef Clear;
		Clear.LayerName = TEXT("Clear");
		Clear.MatchMode = EMapboxLayerMatchMode::Color;
		Clear.TargetColor = FLinearColor::Black;
		Clear.MaterialTint = FLinearColor::Black;
		Clear.Priority = 100;
		Clear.HueTolerance = 0.f;
		Clear.SatTolerance = 0.f;
		Clear.ValTolerance = 0.f; // Disables color match entirely - user paints by hand.
		Clear.bScatterEnabled = false;

		const FMapboxLayerDef Water = MakeVectorLayer(TEXT("Water"), TEXT("water"), {}, 0.f, 90,
			FLinearColor(0.10f, 0.25f, 0.45f));

		const FMapboxLayerDef Buildings = MakeVectorLayer(TEXT("Buildings"), TEXT("building"), {}, 0.f, 80,
			FLinearColor(0.4f, 0.38f, 0.35f));

		const FMapboxLayerDef Runway = MakeVectorLayer(TEXT("Runway"), TEXT("aeroway"),
			{ TEXT("runway") }, 45.f, 75, FLinearColor(0.18f, 0.18f, 0.20f));

		const FMapboxLayerDef Taxiway = MakeVectorLayer(TEXT("Taxiway"), TEXT("aeroway"),
			{ TEXT("taxiway") }, 18.f, 72, FLinearColor(0.22f, 0.22f, 0.22f));

		// Rock - vector landuse=bare_rock, with HSV color fallback for grey escarpments visible in satellite imagery.
		FMapboxLayerDef Rock;
		Rock.LayerName = TEXT("Rock");
		Rock.MatchMode = EMapboxLayerMatchMode::Both;
		Rock.Priority = 70;
		Rock.TargetColor = FLinearColor(0.45f, 0.42f, 0.38f);
		Rock.ColorSpace = EMapboxColorSpace::HSV;
		Rock.HueTolerance = 0.10f;
		Rock.SatTolerance = 0.15f;
		Rock.ValTolerance = 0.20f;
		Rock.MaterialTint = FLinearColor(0.45f, 0.42f, 0.40f);
		Rock.bScatterEnabled = false;
		{
			FMapboxVectorFeatureFilter F;
			F.MvtLayer = TEXT("landuse");
			F.Classes = { TEXT("bare_rock"), TEXT("scree") };
			Rock.VectorFilters.Add(F);
		}

		const FMapboxLayerDef Highway = MakeVectorLayer(TEXT("Highway"), TEXT("road"),
			{ TEXT("motorway"), TEXT("motorway_link"), TEXT("trunk"), TEXT("trunk_link") },
			15.f, 60, FLinearColor(0.25f, 0.25f, 0.27f));

		const FMapboxLayerDef Primary = MakeVectorLayer(TEXT("PrimaryRoad"), TEXT("road"),
			{ TEXT("primary"), TEXT("primary_link"), TEXT("secondary"), TEXT("secondary_link") },
			10.f, 55, FLinearColor(0.32f, 0.32f, 0.34f));

		const FMapboxLayerDef Railway = MakeVectorLayer(TEXT("Railway"), TEXT("road"),
			{ TEXT("major_rail"), TEXT("minor_rail"), TEXT("service_rail") },
			4.f, 52, FLinearColor(0.20f, 0.20f, 0.22f));

		const FMapboxLayerDef Tertiary = MakeVectorLayer(TEXT("TertiaryRoad"), TEXT("road"),
			{ TEXT("tertiary"), TEXT("tertiary_link"), TEXT("street") },
			7.f, 50, FLinearColor(0.38f, 0.38f, 0.40f));

		const FMapboxLayerDef Residential = MakeVectorLayer(TEXT("ResidentialRoad"), TEXT("road"),
			{ TEXT("street_limited"), TEXT("service"), TEXT("track") },
			5.f, 45, FLinearColor(0.45f, 0.45f, 0.47f));

		const FMapboxLayerDef Path = MakeVectorLayer(TEXT("Path"), TEXT("road"),
			{ TEXT("path"), TEXT("footway"), TEXT("pedestrian"), TEXT("steps") },
			2.f, 40, FLinearColor(0.55f, 0.48f, 0.35f));

		const FMapboxLayerDef Forest = MakeVectorLayer(TEXT("Forest"), TEXT("landuse"),
			{ TEXT("wood"), TEXT("forest") },
			0.f, 35, FLinearColor(0.20f, 0.45f, 0.15f), /*bScatter=*/true, /*density=*/4.f, /*minSpacing=*/8.f);

		const FMapboxLayerDef Farmland = MakeVectorLayer(TEXT("Farmland"), TEXT("landuse"),
			{ TEXT("farmland"), TEXT("agriculture"), TEXT("orchard") },
			0.f, 32, FLinearColor(0.55f, 0.42f, 0.25f), /*bScatter=*/false);

		const FMapboxLayerDef Park = MakeVectorLayer(TEXT("Park"), TEXT("landuse"),
			{ TEXT("park"), TEXT("pitch"), TEXT("garden"), TEXT("recreation_ground") },
			0.f, 28, FLinearColor(0.35f, 0.55f, 0.30f), /*bScatter=*/true, /*density=*/8.f, /*minSpacing=*/4.f);

		const FMapboxLayerDef Industrial = MakeVectorLayer(TEXT("Industrial"), TEXT("landuse"),
			{ TEXT("industrial"), TEXT("commercial"), TEXT("parking") },
			0.f, 25, FLinearColor(0.45f, 0.45f, 0.42f));

		const FMapboxLayerDef Mud = MakeVectorLayer(TEXT("Mud"), TEXT("landuse"),
			{ TEXT("wetland"), TEXT("mangrove") },
			0.f, 22, FLinearColor(0.30f, 0.25f, 0.18f), /*bScatter=*/false);

		// Sand - vector natural=sand + landuse=beach
		FMapboxLayerDef Sand = MakeVectorLayer(TEXT("Sand"), TEXT("landuse"),
			{ TEXT("beach"), TEXT("sand") }, 0.f, 20, FLinearColor(0.85f, 0.78f, 0.55f));
		{
			FMapboxVectorFeatureFilter Natural;
			Natural.MvtLayer = TEXT("natural_label");
			Natural.Classes = { TEXT("sand"), TEXT("desert") };
			Sand.VectorFilters.Add(Natural);
		}

		// DrySoil - HSV color fallback for tan/brown ground visible in satellite imagery (fallow farms, bare earth).
		const FMapboxLayerDef DrySoil = MakeColorLayer(TEXT("DrySoil"),
			FLinearColor(0.55f, 0.40f, 0.25f), FLinearColor(0.55f, 0.42f, 0.28f),
			18, /*Hue=*/0.06f, /*Sat=*/0.30f, /*Val=*/0.30f, /*scatter=*/false);

		// Grass - color fallback (greens). Catches everything else.
		const FMapboxLayerDef Grass = MakeColorLayer(TEXT("Grass"),
			FLinearColor(0.55f, 0.70f, 0.30f), FLinearColor(0.45f, 0.55f, 0.25f),
			10, /*Hue=*/0.10f, /*Sat=*/0.40f, /*Val=*/0.40f, /*scatter=*/true, /*density=*/6.f, /*minSpacing=*/3.f);

		DefaultLayers = { Clear, Water, Buildings, Runway, Taxiway, Rock, Highway, Primary,
			Railway, Tertiary, Residential, Path, Forest, Farmland, Park, Industrial, Mud, Sand, DrySoil, Grass };
	}
}
