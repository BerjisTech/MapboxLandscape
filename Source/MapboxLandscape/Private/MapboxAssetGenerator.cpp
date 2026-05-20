#include "MapboxAssetGenerator.h"

#if WITH_EDITOR

#include "AssetRegistry/AssetRegistryModule.h"
#include "Interfaces/IPluginManager.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Misc/PackageName.h"
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

	UMaterialInterface* GetOrCreateDefaultMasterMaterial(const TArray<FName>& /*LayerNames*/)
	{
		const FString AssetPath = GetMasterMaterialAssetPath();

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
		UMaterial* Material = NewObject<UMaterial>(Package, *AssetName, RF_Public | RF_Standalone);
		if (!Material)
		{
			UE_LOG(LogMapboxAssets, Error, TEXT("Mapbox: NewObject<UMaterial> returned null"));
			return nullptr;
		}

		Material->SetShadingModel(MSM_DefaultLit);
		Material->TwoSided = false;
		Material->bUsedWithStaticLighting = true;

		auto AddExpr = [Material](UClass* ExprClass) -> UMaterialExpression*
		{
			UMaterialExpression* Expr = NewObject<UMaterialExpression>(Material, ExprClass);
#if WITH_EDITORONLY_DATA
			Material->GetEditorOnlyData()->ExpressionCollection.Expressions.Add(Expr);
#endif
			return Expr;
		};

		// Minimal, reliable graph: BaseColor = SatelliteTexture parameter; Roughness = 0.85.
		// Layer-aware blending is left to the user; we ship a working baseline so the landscape
		// renders the satellite imagery the moment it's spawned.
		UMaterialExpressionTextureSampleParameter2D* SatTex = Cast<UMaterialExpressionTextureSampleParameter2D>(
			AddExpr(UMaterialExpressionTextureSampleParameter2D::StaticClass()));
		SatTex->ParameterName = TEXT("SatelliteTexture");
		SatTex->MaterialExpressionEditorX = -400;
		SatTex->MaterialExpressionEditorY = 0;

		UMaterialExpressionConstant* Roughness = Cast<UMaterialExpressionConstant>(
			AddExpr(UMaterialExpressionConstant::StaticClass()));
		Roughness->R = 0.85f;
		Roughness->MaterialExpressionEditorX = -400;
		Roughness->MaterialExpressionEditorY = 240;

#if WITH_EDITORONLY_DATA
		auto& EditorOnly = *Material->GetEditorOnlyData();
		EditorOnly.BaseColor.Expression = SatTex;
		EditorOnly.Roughness.Expression = Roughness;
#endif

		Material->PreEditChange(nullptr);
		Material->PostEditChange();
		Material->ForceRecompileForRendering();

		SavePackageToDisk(Package, Material);
		UE_LOG(LogMapboxAssets, Log, TEXT("Mapbox: created master material %s"), *AssetPath);
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
	UMaterialInterface* GetOrCreateDefaultMasterMaterial(const TArray<FName>&) { return nullptr; }
	UMaterialInterface* GetOrCreateDefaultDecalMaterial() { return nullptr; }
	UPCGGraphInterface* GetOrCreateDefaultScatterGraph() { return nullptr; }
}

#endif
