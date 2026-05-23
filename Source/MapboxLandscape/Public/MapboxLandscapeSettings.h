#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MapboxLayerDef.h"
#include "MapboxLandscapeSettings.generated.h"

class UMaterialInterface;
class UPCGGraphInterface;

UCLASS(config = MapboxLandscape, defaultconfig, meta = (DisplayName = "Mapbox Landscape"))
class MAPBOXLANDSCAPE_API UMapboxLandscapeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UMapboxLandscapeSettings();

	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }

	// --- Authentication ---
	UPROPERTY(EditAnywhere, config, Category = "API", meta = (ToolTip = "Your Mapbox access token. Stored in DefaultMapboxLandscape.ini."))
	FString ApiKey;

	// --- Mapbox TOS acknowledgement ---
	// Persisted so the Importer panel only shows the TOS banner until the user clicks
	// "I understand". Per-project (DefaultMapboxLandscape.ini) rather than per-user — if
	// you open someone else's project you'll see the banner again, which is the safer
	// default because the consent is contextual to the work being done.
	UPROPERTY(config)
	bool bAcceptedMapboxTerms = false;

	// --- Tile defaults ---
	UPROPERTY(EditAnywhere, config, Category = "Defaults|Tiling")
	FString DefaultMetadataStyleId = TEXT("mapbox/satellite-streets-v12");

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Tiling")
	bool bDefaultAutoZoom = true;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Tiling", meta = (ClampMin = "8", ClampMax = "18"))
	int32 DefaultZoomLevel = 14;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Tiling", meta = (ClampMin = "1", ClampMax = "16"))
	int32 DefaultTilesPerLandscapeSide = 4;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Tiling", meta = (ClampMin = "1", ClampMax = "256"))
	int32 DefaultMaxLandscapesTotal = 64;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Tiling", meta = (ClampMin = "1", ClampMax = "64"))
	int32 DefaultMaxConcurrentRequests = 16;

	// --- Elevation defaults ---
	UPROPERTY(EditAnywhere, config, Category = "Defaults|Elevation", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float DefaultZExaggeration = 1.0f;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Elevation")
	bool bDefaultRebaseToSeaLevel = true;

	// --- Satellite defaults ---
	UPROPERTY(EditAnywhere, config, Category = "Defaults|Satellite")
	EMapboxSatelliteMode DefaultSatelliteMode = EMapboxSatelliteMode::BlendIntoMaterial;

	// --- Coordinate defaults (for new actors) ---
	UPROPERTY(EditAnywhere, config, Category = "Defaults|Coordinates")
	double DefaultCenterLatitude = -1.2921;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Coordinates")
	double DefaultCenterLongitude = 36.8219;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Coordinates", meta = (ClampMin = "0.1", ClampMax = "200.0"))
	double DefaultRadiusKm = 5.0;

	// --- Material / PCG defaults ---
	UPROPERTY(EditAnywhere, config, Category = "Defaults|Material", meta = (ToolTip = "Default master landscape material. Empty = auto-generate M_MapboxLandscape."))
	TSoftObjectPtr<UMaterialInterface> DefaultLandscapeMasterMaterial;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|Material")
	bool bDefaultAutoGenerateAssets = true;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|PCG")
	TSoftObjectPtr<UPCGGraphInterface> DefaultScatterPCGGraph;

	UPROPERTY(EditAnywhere, config, Category = "Defaults|PCG", meta = (ToolTip = "Default for whether to attach a UPCGComponent to each spawned landscape. Defaults to OFF because synchronous PCG generation across many landscapes stalls the editor; the built-in HISM scatter still runs as a baseline."))
	bool bDefaultSpawnPCGComponents = false;

	// --- Layer rules ---
	UPROPERTY(EditAnywhere, config, Category = "Defaults|Layers", meta = (ToolTip = "Default layer classification + scatter rules. New actors copy this on placement; existing actors keep their per-instance overrides."))
	TArray<FMapboxLayerDef> DefaultLayers;

	static const UMapboxLandscapeSettings* Get() { return GetDefault<UMapboxLandscapeSettings>(); }
};
