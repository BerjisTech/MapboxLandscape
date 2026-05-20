#include "MapboxLandscapeSettings.h"

UMapboxLandscapeSettings::UMapboxLandscapeSettings()
{
	if (DefaultLayers.IsEmpty())
	{
		FMapboxLayerDef Forest;
		Forest.LayerName = TEXT("Forest");
		Forest.TargetColor = FLinearColor(0.30f, 0.55f, 0.20f);
		Forest.MaterialTint = FLinearColor(0.20f, 0.45f, 0.15f);
		Forest.Priority = 30;
		Forest.ScatterDensity = 4.f;

		FMapboxLayerDef Grass;
		Grass.LayerName = TEXT("Grass");
		Grass.TargetColor = FLinearColor(0.55f, 0.70f, 0.30f);
		Grass.MaterialTint = FLinearColor(0.45f, 0.55f, 0.25f);
		Grass.Priority = 20;
		Grass.ScatterDensity = 12.f;

		FMapboxLayerDef Urban;
		Urban.LayerName = TEXT("Urban");
		Urban.TargetColor = FLinearColor(0.65f, 0.65f, 0.65f);
		Urban.ColorSpace = EMapboxColorSpace::HSV;
		Urban.SatTolerance = 0.15f;
		Urban.MaterialTint = FLinearColor(0.5f, 0.5f, 0.5f);
		Urban.Priority = 40;
		Urban.bScatterEnabled = false;

		FMapboxLayerDef Road;
		Road.LayerName = TEXT("Road");
		Road.TargetColor = FLinearColor(0.85f, 0.85f, 0.85f);
		Road.ColorSpace = EMapboxColorSpace::HSV;
		Road.SatTolerance = 0.1f;
		Road.MaterialTint = FLinearColor(0.3f, 0.3f, 0.3f);
		Road.Priority = 50;
		Road.bScatterEnabled = false;

		FMapboxLayerDef Water;
		Water.LayerName = TEXT("Water");
		Water.TargetColor = FLinearColor(0.20f, 0.40f, 0.65f);
		Water.MaterialTint = FLinearColor(0.10f, 0.25f, 0.45f);
		Water.Priority = 60;
		Water.bScatterEnabled = false;

		DefaultLayers = { Forest, Grass, Urban, Road, Water };
	}
}
