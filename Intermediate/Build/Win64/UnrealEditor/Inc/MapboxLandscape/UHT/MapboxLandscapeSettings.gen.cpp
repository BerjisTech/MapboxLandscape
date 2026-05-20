// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MapboxLandscapeSettings.h"
#include "MapboxLayerDef.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMapboxLandscapeSettings() {}

// ********** Begin Cross Module References ********************************************************
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_UMapboxLandscapeSettings();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_UMapboxLandscapeSettings_NoRegister();
MAPBOXLANDSCAPE_API UEnum* Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode();
MAPBOXLANDSCAPE_API UScriptStruct* Z_Construct_UScriptStruct_FMapboxLayerDef();
PCG_API UClass* Z_Construct_UClass_UPCGGraphInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_MapboxLandscape();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMapboxLandscapeSettings *************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMapboxLandscapeSettings;
UClass* UMapboxLandscapeSettings::GetPrivateStaticClass()
{
	using TClass = UMapboxLandscapeSettings;
	if (!Z_Registration_Info_UClass_UMapboxLandscapeSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MapboxLandscapeSettings"),
			Z_Registration_Info_UClass_UMapboxLandscapeSettings.InnerSingleton,
			StaticRegisterNativesUMapboxLandscapeSettings,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UMapboxLandscapeSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UMapboxLandscapeSettings_NoRegister()
{
	return UMapboxLandscapeSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMapboxLandscapeSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "DisplayName", "Mapbox Landscape" },
		{ "IncludePath", "MapboxLandscapeSettings.h" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApiKey_MetaData[] = {
		{ "Category", "API" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Your Mapbox access token. Stored in DefaultMapboxLandscape.ini." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMetadataStyleId_MetaData[] = {
		{ "Category", "Defaults|Tiling" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Tile defaults ---\n" },
#endif
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Tile defaults ---" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDefaultAutoZoom_MetaData[] = {
		{ "Category", "Defaults|Tiling" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultZoomLevel_MetaData[] = {
		{ "Category", "Defaults|Tiling" },
		{ "ClampMax", "18" },
		{ "ClampMin", "8" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultTilesPerLandscapeSide_MetaData[] = {
		{ "Category", "Defaults|Tiling" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMaxLandscapesTotal_MetaData[] = {
		{ "Category", "Defaults|Tiling" },
		{ "ClampMax", "256" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMaxConcurrentRequests_MetaData[] = {
		{ "Category", "Defaults|Tiling" },
		{ "ClampMax", "64" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultZExaggeration_MetaData[] = {
		{ "Category", "Defaults|Elevation" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Elevation defaults ---\n" },
#endif
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Elevation defaults ---" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDefaultRebaseToSeaLevel_MetaData[] = {
		{ "Category", "Defaults|Elevation" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultSatelliteMode_MetaData[] = {
		{ "Category", "Defaults|Satellite" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Satellite defaults ---\n" },
#endif
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Satellite defaults ---" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultCenterLatitude_MetaData[] = {
		{ "Category", "Defaults|Coordinates" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- Coordinate defaults (for new actors) ---\n" },
#endif
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- Coordinate defaults (for new actors) ---" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultCenterLongitude_MetaData[] = {
		{ "Category", "Defaults|Coordinates" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultRadiusKm_MetaData[] = {
		{ "Category", "Defaults|Coordinates" },
		{ "ClampMax", "200.0" },
		{ "ClampMin", "0.1" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultLandscapeMasterMaterial_MetaData[] = {
		{ "Category", "Defaults|Material" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default master landscape material. Empty = auto-generate M_MapboxLandscape." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDefaultAutoGenerateAssets_MetaData[] = {
		{ "Category", "Defaults|Material" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultScatterPCGGraph_MetaData[] = {
		{ "Category", "Defaults|PCG" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDefaultSpawnPCGComponents_MetaData[] = {
		{ "Category", "Defaults|PCG" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultLayers_MetaData[] = {
		{ "Category", "Defaults|Layers" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default layer classification + scatter rules. New actors copy this on placement; existing actors keep their per-instance overrides." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UMapboxLandscapeSettings constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ApiKey;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultMetadataStyleId;
	static void NewProp_bDefaultAutoZoom_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDefaultAutoZoom;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DefaultZoomLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DefaultTilesPerLandscapeSide;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DefaultMaxLandscapesTotal;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DefaultMaxConcurrentRequests;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultZExaggeration;
	static void NewProp_bDefaultRebaseToSeaLevel_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDefaultRebaseToSeaLevel;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DefaultSatelliteMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DefaultSatelliteMode;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_DefaultCenterLatitude;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_DefaultCenterLongitude;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_DefaultRadiusKm;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_DefaultLandscapeMasterMaterial;
	static void NewProp_bDefaultAutoGenerateAssets_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDefaultAutoGenerateAssets;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_DefaultScatterPCGGraph;
	static void NewProp_bDefaultSpawnPCGComponents_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDefaultSpawnPCGComponents;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DefaultLayers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultLayers;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UMapboxLandscapeSettings constinit property declarations *******************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMapboxLandscapeSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMapboxLandscapeSettings_Statics

// ********** Begin Class UMapboxLandscapeSettings Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_ApiKey = { "ApiKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, ApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApiKey_MetaData), NewProp_ApiKey_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultMetadataStyleId = { "DefaultMetadataStyleId", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultMetadataStyleId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMetadataStyleId_MetaData), NewProp_DefaultMetadataStyleId_MetaData) };
void Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoZoom_SetBit(void* Obj)
{
	((UMapboxLandscapeSettings*)Obj)->bDefaultAutoZoom = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoZoom = { "bDefaultAutoZoom", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMapboxLandscapeSettings), &Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoZoom_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDefaultAutoZoom_MetaData), NewProp_bDefaultAutoZoom_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultZoomLevel = { "DefaultZoomLevel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultZoomLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultZoomLevel_MetaData), NewProp_DefaultZoomLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultTilesPerLandscapeSide = { "DefaultTilesPerLandscapeSide", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultTilesPerLandscapeSide), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultTilesPerLandscapeSide_MetaData), NewProp_DefaultTilesPerLandscapeSide_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultMaxLandscapesTotal = { "DefaultMaxLandscapesTotal", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultMaxLandscapesTotal), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMaxLandscapesTotal_MetaData), NewProp_DefaultMaxLandscapesTotal_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultMaxConcurrentRequests = { "DefaultMaxConcurrentRequests", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultMaxConcurrentRequests), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMaxConcurrentRequests_MetaData), NewProp_DefaultMaxConcurrentRequests_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultZExaggeration = { "DefaultZExaggeration", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultZExaggeration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultZExaggeration_MetaData), NewProp_DefaultZExaggeration_MetaData) };
void Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultRebaseToSeaLevel_SetBit(void* Obj)
{
	((UMapboxLandscapeSettings*)Obj)->bDefaultRebaseToSeaLevel = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultRebaseToSeaLevel = { "bDefaultRebaseToSeaLevel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMapboxLandscapeSettings), &Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultRebaseToSeaLevel_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDefaultRebaseToSeaLevel_MetaData), NewProp_bDefaultRebaseToSeaLevel_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultSatelliteMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultSatelliteMode = { "DefaultSatelliteMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultSatelliteMode), Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultSatelliteMode_MetaData), NewProp_DefaultSatelliteMode_MetaData) }; // 1775657975
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultCenterLatitude = { "DefaultCenterLatitude", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultCenterLatitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultCenterLatitude_MetaData), NewProp_DefaultCenterLatitude_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultCenterLongitude = { "DefaultCenterLongitude", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultCenterLongitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultCenterLongitude_MetaData), NewProp_DefaultCenterLongitude_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultRadiusKm = { "DefaultRadiusKm", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultRadiusKm), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultRadiusKm_MetaData), NewProp_DefaultRadiusKm_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultLandscapeMasterMaterial = { "DefaultLandscapeMasterMaterial", nullptr, (EPropertyFlags)0x0014000000004001, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultLandscapeMasterMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultLandscapeMasterMaterial_MetaData), NewProp_DefaultLandscapeMasterMaterial_MetaData) };
void Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoGenerateAssets_SetBit(void* Obj)
{
	((UMapboxLandscapeSettings*)Obj)->bDefaultAutoGenerateAssets = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoGenerateAssets = { "bDefaultAutoGenerateAssets", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMapboxLandscapeSettings), &Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoGenerateAssets_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDefaultAutoGenerateAssets_MetaData), NewProp_bDefaultAutoGenerateAssets_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultScatterPCGGraph = { "DefaultScatterPCGGraph", nullptr, (EPropertyFlags)0x0014000000004001, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultScatterPCGGraph), Z_Construct_UClass_UPCGGraphInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultScatterPCGGraph_MetaData), NewProp_DefaultScatterPCGGraph_MetaData) };
void Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultSpawnPCGComponents_SetBit(void* Obj)
{
	((UMapboxLandscapeSettings*)Obj)->bDefaultSpawnPCGComponents = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultSpawnPCGComponents = { "bDefaultSpawnPCGComponents", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMapboxLandscapeSettings), &Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultSpawnPCGComponents_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDefaultSpawnPCGComponents_MetaData), NewProp_bDefaultSpawnPCGComponents_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultLayers_Inner = { "DefaultLayers", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMapboxLayerDef, METADATA_PARAMS(0, nullptr) }; // 1586647006
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultLayers = { "DefaultLayers", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMapboxLandscapeSettings, DefaultLayers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultLayers_MetaData), NewProp_DefaultLayers_MetaData) }; // 1586647006
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMapboxLandscapeSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_ApiKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultMetadataStyleId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoZoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultZoomLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultTilesPerLandscapeSide,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultMaxLandscapesTotal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultMaxConcurrentRequests,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultZExaggeration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultRebaseToSeaLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultSatelliteMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultSatelliteMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultCenterLatitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultCenterLongitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultRadiusKm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultLandscapeMasterMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultAutoGenerateAssets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultScatterPCGGraph,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_bDefaultSpawnPCGComponents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultLayers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMapboxLandscapeSettings_Statics::NewProp_DefaultLayers,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMapboxLandscapeSettings_Statics::PropPointers) < 2048);
// ********** End Class UMapboxLandscapeSettings Property Definitions ******************************
UObject* (*const Z_Construct_UClass_UMapboxLandscapeSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_MapboxLandscape,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMapboxLandscapeSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMapboxLandscapeSettings_Statics::ClassParams = {
	&UMapboxLandscapeSettings::StaticClass,
	"MapboxLandscape",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UMapboxLandscapeSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UMapboxLandscapeSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMapboxLandscapeSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UMapboxLandscapeSettings_Statics::Class_MetaDataParams)
};
void UMapboxLandscapeSettings::StaticRegisterNativesUMapboxLandscapeSettings()
{
}
UClass* Z_Construct_UClass_UMapboxLandscapeSettings()
{
	if (!Z_Registration_Info_UClass_UMapboxLandscapeSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMapboxLandscapeSettings.OuterSingleton, Z_Construct_UClass_UMapboxLandscapeSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMapboxLandscapeSettings.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMapboxLandscapeSettings);
UMapboxLandscapeSettings::~UMapboxLandscapeSettings() {}
// ********** End Class UMapboxLandscapeSettings ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h__Script_MapboxLandscape_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMapboxLandscapeSettings, UMapboxLandscapeSettings::StaticClass, TEXT("UMapboxLandscapeSettings"), &Z_Registration_Info_UClass_UMapboxLandscapeSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMapboxLandscapeSettings), 3070434076U) },
	};
}; // Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h__Script_MapboxLandscape_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h__Script_MapboxLandscape_2013525222{
	TEXT("/Script/MapboxLandscape"),
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h__Script_MapboxLandscape_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h__Script_MapboxLandscape_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
