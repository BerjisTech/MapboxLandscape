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

USTRUCT(BlueprintType)
struct FMapboxLayerDef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layer")
	FName LayerName = TEXT("NewLayer");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match")
	FLinearColor TargetColor = FLinearColor(0.3f, 0.6f, 0.2f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match")
	EMapboxColorSpace ColorSpace = EMapboxColorSpace::HSV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HueTolerance = 0.08f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float SatTolerance = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ValTolerance = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Match", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "ColorSpace == EMapboxColorSpace::RGB", EditConditionHides))
	float RGBTolerance = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layer", meta = (ClampMin = "0", ClampMax = "100"))
	int32 Priority = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FLinearColor MaterialTint = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TSoftObjectPtr<UTexture2D> AlbedoTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TSoftObjectPtr<UPhysicalMaterial> PhysicalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter")
	bool bScatterEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled"))
	TArray<TSoftObjectPtr<UStaticMesh>> ScatterMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "0.0", ToolTip = "Average meshes per 100 square meters."))
	float ScatterDensity = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "0.0"))
	float ScatterMinScale = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled", ClampMin = "0.0"))
	float ScatterMaxScale = 1.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled"))
	bool bRandomYaw = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scatter", meta = (EditCondition = "bScatterEnabled"))
	bool bAlignToLandscapeNormal = false;
};
