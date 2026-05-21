#include "MapboxAssetGenerator.h"

#if WITH_EDITOR

#include "AssetRegistry/AssetRegistryModule.h"
#include "Interfaces/IPluginManager.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionComponentMask.h"
#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionDivide.h"
#include "Materials/MaterialExpressionLandscapeLayerWeight.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionSubtract.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialExpressionWorldPosition.h"
#include "Misc/PackageName.h"
#include "ObjectTools.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"

#include "PCGGraph.h"

DEFINE_LOG_CATEGORY_STATIC(LogMapboxAssets, Log, All);

namespace MapboxAssetGenerator
{
	FString GetPluginContentDir()
	{
		TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("MapboxLandscape"));
		return Plugin.IsValid() ? Plugin->GetContentDir() : FString();
	}

	FString GetMasterMaterialAssetPath()
	{
		// Writing to /Game/ avoids plugin-content mount-point edge cases.
		return TEXT("/Game/MapboxLandscape/Materials/M_MapboxLandscape");
	}

	FString GetScatterGraphAssetPath()
	{
		return TEXT("/Game/MapboxLandscape/PCG/PCG_MapboxScatter");
	}

	FString GetDecalMaterialAssetPath()
	{
		return TEXT("/Game/MapboxLandscape/Materials/M_MapboxSatelliteDecal");
	}

	static UPackage* CreateOrLoadPackage(const FString& AssetPath)
	{
		const FString PackagePath = FPackageName::ObjectPathToPackageName(AssetPath);
		UPackage* Package = CreatePackage(*PackagePath);
		if (Package)
		{
			Package->FullyLoad();
		}
		return Package;
	}

	static bool SavePackageToDisk(UPackage* Package, UObject* Asset)
	{
		if (!Package || !Asset) return false;

		FAssetRegistryModule::AssetCreated(Asset);
		Asset->MarkPackageDirty();

		const FString PackageFilename = FPackageName::LongPackageNameToFilename(
			Package->GetName(), FPackageName::GetAssetPackageExtension());

		FSavePackageArgs SaveArgs;
		SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		SaveArgs.SaveFlags = SAVE_NoError;

		const bool bSaved = UPackage::SavePackage(Package, Asset, *PackageFilename, SaveArgs);
		if (!bSaved)
		{
			UE_LOG(LogMapboxAssets, Warning, TEXT("Mapbox: failed to save %s"), *Package->GetName());
		}
		return bSaved;
	}

	UMaterialInterface* GetOrCreateDefaultMasterMaterial(const TArray<FName>& /*LayerNames*/, bool bForceRecreate)
	{
		const FString AssetPath = GetMasterMaterialAssetPath();

		if (!bForceRecreate)
		{
			if (UMaterial* Existing = LoadObject<UMaterial>(nullptr, *AssetPath))
			{
				return Existing;
			}
		}
		else
		{
			// Delete the stale material so we don't accumulate _NN suffix duplicates.
			if (UMaterial* Existing = LoadObject<UMaterial>(nullptr, *AssetPath))
			{
				TArray<UObject*> ToDelete = { Existing };
				ObjectTools::ForceDeleteObjects(ToDelete, /*bShowConfirmation=*/false);
			}
		}

		UPackage* Package = CreateOrLoadPackage(AssetPath);
		if (!Package)
		{
			UE_LOG(LogMapboxAssets, Error, TEXT("Mapbox: failed to create package for %s"), *AssetPath);
			return nullptr;
		}

		const FString AssetName = FPackageName::GetShortName(AssetPath);
		UMaterial* Material = NewObject<UMaterial>(Package, *AssetName, RF_Public | RF_Standalone);
		if (!Material)
		{
			UE_LOG(LogMapboxAssets, Error, TEXT("Mapbox: NewObject<UMaterial> returned null"));
			return nullptr;
		}

		Material->SetShadingModel(MSM_DefaultLit);
		Material->TwoSided = false;
		Material->bUsedWithStaticLighting = true;
		// Masked so the "Clear" landscape weight layer can cut holes in the surface (carved hills / hidden sections).
		Material->BlendMode = BLEND_Masked;
		Material->OpacityMaskClipValue = 0.5f;

		auto AddExpr = [Material](UClass* ExprClass) -> UMaterialExpression*
		{
			UMaterialExpression* Expr = NewObject<UMaterialExpression>(Material, ExprClass);
#if WITH_EDITORONLY_DATA
			Material->GetEditorOnlyData()->ExpressionCollection.Expressions.Add(Expr);
#endif
			return Expr;
		};

		// Build world-space UVs so the satellite texture maps exactly ONCE across the chunk
		// regardless of landscape resolution. UV = (WorldPos.xy - LandscapeOrigin.xy) / LandscapeWorldSize
		// MICs created per-chunk set both parameters.
		UMaterialExpressionWorldPosition* WorldPos = Cast<UMaterialExpressionWorldPosition>(
			AddExpr(UMaterialExpressionWorldPosition::StaticClass()));
		WorldPos->MaterialExpressionEditorX = -1100;
		WorldPos->MaterialExpressionEditorY = -100;

		UMaterialExpressionComponentMask* WorldPosXY = Cast<UMaterialExpressionComponentMask>(
			AddExpr(UMaterialExpressionComponentMask::StaticClass()));
		WorldPosXY->R = 1; WorldPosXY->G = 1; WorldPosXY->B = 0; WorldPosXY->A = 0;
		WorldPosXY->Input.Expression = WorldPos;
		WorldPosXY->MaterialExpressionEditorX = -900;
		WorldPosXY->MaterialExpressionEditorY = -100;

		UMaterialExpressionVectorParameter* OriginParam = Cast<UMaterialExpressionVectorParameter>(
			AddExpr(UMaterialExpressionVectorParameter::StaticClass()));
		OriginParam->ParameterName = TEXT("LandscapeOrigin");
		OriginParam->DefaultValue = FLinearColor(0, 0, 0, 0);
		OriginParam->MaterialExpressionEditorX = -1100;
		OriginParam->MaterialExpressionEditorY = 80;

		UMaterialExpressionComponentMask* OriginXY = Cast<UMaterialExpressionComponentMask>(
			AddExpr(UMaterialExpressionComponentMask::StaticClass()));
		OriginXY->R = 1; OriginXY->G = 1; OriginXY->B = 0; OriginXY->A = 0;
		OriginXY->Input.Expression = OriginParam;
		OriginXY->MaterialExpressionEditorX = -900;
		OriginXY->MaterialExpressionEditorY = 80;

		UMaterialExpressionSubtract* Localized = Cast<UMaterialExpressionSubtract>(
			AddExpr(UMaterialExpressionSubtract::StaticClass()));
		Localized->A.Expression = WorldPosXY;
		Localized->B.Expression = OriginXY;
		Localized->MaterialExpressionEditorX = -700;
		Localized->MaterialExpressionEditorY = -10;

		UMaterialExpressionScalarParameter* SizeParam = Cast<UMaterialExpressionScalarParameter>(
			AddExpr(UMaterialExpressionScalarParameter::StaticClass()));
		SizeParam->ParameterName = TEXT("LandscapeWorldSize");
		SizeParam->DefaultValue = 100000.f; // 1km fallback so editor preview shows something
		SizeParam->MaterialExpressionEditorX = -700;
		SizeParam->MaterialExpressionEditorY = 160;

		UMaterialExpressionDivide* UVs = Cast<UMaterialExpressionDivide>(
			AddExpr(UMaterialExpressionDivide::StaticClass()));
		UVs->A.Expression = Localized;
		UVs->B.Expression = SizeParam;
		UVs->MaterialExpressionEditorX = -500;
		UVs->MaterialExpressionEditorY = 0;

		// Satellite texture sample, fed by the computed UVs (NOT default per-vertex UVs).
		UMaterialExpressionTextureSampleParameter2D* SatTex = Cast<UMaterialExpressionTextureSampleParameter2D>(
			AddExpr(UMaterialExpressionTextureSampleParameter2D::StaticClass()));
		SatTex->ParameterName = TEXT("SatelliteTexture");
		// TextureSampleParameter2D requires a default texture for the material to compile.
		if (UTexture2D* DefaultTex = LoadObject<UTexture2D>(nullptr, TEXT("/Engine/EngineResources/DefaultTexture.DefaultTexture")))
		{
			SatTex->Texture = DefaultTex;
		}
		SatTex->SamplerType = SAMPLERTYPE_Color;
		SatTex->Coordinates.Expression = UVs;
		SatTex->MaterialExpressionEditorX = -250;
		SatTex->MaterialExpressionEditorY = 0;

		UMaterialExpressionConstant* Roughness = Cast<UMaterialExpressionConstant>(
			AddExpr(UMaterialExpressionConstant::StaticClass()));
		Roughness->R = 0.85f;
		Roughness->MaterialExpressionEditorX = -250;
		Roughness->MaterialExpressionEditorY = 240;

		// "Clear" landscape layer drives opacity. Weight 1.0 -> opacity 0 -> pixel discarded (cut a hole / carve hill).
		// Weight 0.0 -> opacity 1 -> pixel renders normally. Routed via LandscapeLayerWeight expression so the
		// landscape system feeds the per-pixel layer alpha directly.
		UMaterialExpressionLandscapeLayerWeight* ClearWeight = Cast<UMaterialExpressionLandscapeLayerWeight>(
			AddExpr(UMaterialExpressionLandscapeLayerWeight::StaticClass()));
		ClearWeight->ParameterName = TEXT("Clear");
		ClearWeight->PreviewWeight = 0.f;
		ClearWeight->MaterialExpressionEditorX = -500;
		ClearWeight->MaterialExpressionEditorY = 400;

		// Constant 1.0 fed into ConstBase so the unweighted ("Clear==0") output is 1.0.
		UMaterialExpressionConstant* OneConst = Cast<UMaterialExpressionConstant>(
			AddExpr(UMaterialExpressionConstant::StaticClass()));
		OneConst->R = 1.0f;
		OneConst->MaterialExpressionEditorX = -700;
		OneConst->MaterialExpressionEditorY = 460;
		ClearWeight->Base.Expression = OneConst;

		// Constant 0.0 fed into Layer input so the weighted ("Clear==1") output is 0.0.
		UMaterialExpressionConstant* ZeroConst = Cast<UMaterialExpressionConstant>(
			AddExpr(UMaterialExpressionConstant::StaticClass()));
		ZeroConst->R = 0.0f;
		ZeroConst->MaterialExpressionEditorX = -700;
		ZeroConst->MaterialExpressionEditorY = 540;
		ClearWeight->Layer.Expression = ZeroConst;

#if WITH_EDITORONLY_DATA
		auto& EditorOnly = *Material->GetEditorOnlyData();
		EditorOnly.BaseColor.Expression = SatTex;
		EditorOnly.Roughness.Expression = Roughness;
		EditorOnly.OpacityMask.Expression = ClearWeight;
#endif

		Material->PreEditChange(nullptr);
		Material->PostEditChange();
		Material->ForceRecompileForRendering();

		SavePackageToDisk(Package, Material);
		UE_LOG(LogMapboxAssets, Log, TEXT("Mapbox: created master material %s (version %d)"), *AssetPath, MasterMaterialVersion);
		return Material;
	}

	UMaterialInterface* GetOrCreateDefaultDecalMaterial()
	{
		const FString AssetPath = GetDecalMaterialAssetPath();
		if (UMaterial* Existing = LoadObject<UMaterial>(nullptr, *AssetPath))
		{
			return Existing;
		}

		UPackage* Package = CreateOrLoadPackage(AssetPath);
		if (!Package)
		{
			UE_LOG(LogMapboxAssets, Error, TEXT("Mapbox: failed to create package for %s"), *AssetPath);
			return nullptr;
		}

		const FString AssetName = FPackageName::GetShortName(AssetPath);
		UMaterial* Mat = NewObject<UMaterial>(Package, *AssetName, RF_Public | RF_Standalone);
		if (!Mat)
		{
			return nullptr;
		}

		Mat->MaterialDomain = MD_DeferredDecal;
		Mat->BlendMode = BLEND_Translucent;

		auto AddExpr = [Mat](UClass* Cls) -> UMaterialExpression*
		{
			UMaterialExpression* E = NewObject<UMaterialExpression>(Mat, Cls);
#if WITH_EDITORONLY_DATA
			Mat->GetEditorOnlyData()->ExpressionCollection.Expressions.Add(E);
#endif
			return E;
		};

		UMaterialExpressionTextureSampleParameter2D* Tex = Cast<UMaterialExpressionTextureSampleParameter2D>(
			AddExpr(UMaterialExpressionTextureSampleParameter2D::StaticClass()));
		Tex->ParameterName = TEXT("SatelliteTexture");
		if (UTexture2D* DefaultTex = LoadObject<UTexture2D>(nullptr, TEXT("/Engine/EngineResources/DefaultTexture.DefaultTexture")))
		{
			Tex->Texture = DefaultTex;
		}
		Tex->SamplerType = SAMPLERTYPE_Color;

		UMaterialExpressionScalarParameter* Opacity = Cast<UMaterialExpressionScalarParameter>(
			AddExpr(UMaterialExpressionScalarParameter::StaticClass()));
		Opacity->ParameterName = TEXT("Opacity");
		Opacity->DefaultValue = 1.f;

#if WITH_EDITORONLY_DATA
		auto& Ed = *Mat->GetEditorOnlyData();
		Ed.BaseColor.Expression = Tex;
		Ed.Opacity.Expression = Opacity;
#endif

		Mat->PreEditChange(nullptr);
		Mat->PostEditChange();
		Mat->ForceRecompileForRendering();

		SavePackageToDisk(Package, Mat);
		UE_LOG(LogMapboxAssets, Log, TEXT("Mapbox: created decal material %s"), *AssetPath);
		return Mat;
	}

	UPCGGraphInterface* GetOrCreateDefaultScatterGraph()
	{
		const FString AssetPath = GetScatterGraphAssetPath();
		if (UPCGGraphInterface* Existing = LoadObject<UPCGGraphInterface>(nullptr, *AssetPath))
		{
			return Existing;
		}

		UPackage* Package = CreateOrLoadPackage(AssetPath);
		if (!Package) return nullptr;

		const FString AssetName = FPackageName::GetShortName(AssetPath);
		UPCGGraph* Graph = NewObject<UPCGGraph>(Package, *AssetName, RF_Public | RF_Standalone);
		if (!Graph) return nullptr;

		SavePackageToDisk(Package, Graph);
		return Graph;
	}
}

#else // !WITH_EDITOR

namespace MapboxAssetGenerator
{
	FString GetPluginContentDir() { return FString(); }
	FString GetMasterMaterialAssetPath() { return FString(); }
	FString GetDecalMaterialAssetPath() { return FString(); }
	FString GetScatterGraphAssetPath() { return FString(); }
	UMaterialInterface* GetOrCreateDefaultMasterMaterial(const TArray<FName>&, bool) { return nullptr; }
	UMaterialInterface* GetOrCreateDefaultDecalMaterial() { return nullptr; }
	UPCGGraphInterface* GetOrCreateDefaultScatterGraph() { return nullptr; }
}

#endif
