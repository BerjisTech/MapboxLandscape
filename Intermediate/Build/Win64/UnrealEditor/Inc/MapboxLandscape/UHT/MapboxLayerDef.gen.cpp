// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MapboxLayerDef.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMapboxLayerDef() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
MAPBOXLANDSCAPE_API UEnum* Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace();
MAPBOXLANDSCAPE_API UEnum* Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode();
MAPBOXLANDSCAPE_API UScriptStruct* Z_Construct_UScriptStruct_FMapboxLayerDef();
PHYSICSCORE_API UClass* Z_Construct_UClass_UPhysicalMaterial_NoRegister();
UPackage* Z_Construct_UPackage__Script_MapboxLandscape();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EMapboxColorSpace *********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMapboxColorSpace;
static UEnum* EMapboxColorSpace_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EMapboxColorSpace.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EMapboxColorSpace.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace, (UObject*)Z_Construct_UPackage__Script_MapboxLandscape(), TEXT("EMapboxColorSpace"));
	}
	return Z_Registration_Info_UEnum_EMapboxColorSpace.OuterSingleton;
}
template<> MAPBOXLANDSCAPE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMapboxColorSpace>()
{
	return EMapboxColorSpace_StaticEnum();
}
struct Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "HSV.DisplayName", "HSV (hue-aware, recommended for natural colors)" },
		{ "HSV.Name", "EMapboxColorSpace::HSV" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
		{ "RGB.DisplayName", "RGB (linear distance)" },
		{ "RGB.Name", "EMapboxColorSpace::RGB" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMapboxColorSpace::RGB", (int64)EMapboxColorSpace::RGB },
		{ "EMapboxColorSpace::HSV", (int64)EMapboxColorSpace::HSV },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_MapboxLandscape,
	nullptr,
	"EMapboxColorSpace",
	"EMapboxColorSpace",
	Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics::Enum_MetaDataParams), Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace()
{
	if (!Z_Registration_Info_UEnum_EMapboxColorSpace.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMapboxColorSpace.InnerSingleton, Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EMapboxColorSpace.InnerSingleton;
}
// ********** End Enum EMapboxColorSpace ***********************************************************

// ********** Begin Enum EMapboxSatelliteMode ******************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMapboxSatelliteMode;
static UEnum* EMapboxSatelliteMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EMapboxSatelliteMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EMapboxSatelliteMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode, (UObject*)Z_Construct_UPackage__Script_MapboxLandscape(), TEXT("EMapboxSatelliteMode"));
	}
	return Z_Registration_Info_UEnum_EMapboxSatelliteMode.OuterSingleton;
}
template<> MAPBOXLANDSCAPE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMapboxSatelliteMode>()
{
	return EMapboxSatelliteMode_StaticEnum();
}
struct Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlendIntoMaterial.DisplayName", "Blend Into Landscape Material" },
		{ "BlendIntoMaterial.Name", "EMapboxSatelliteMode::BlendIntoMaterial" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "EMapboxSatelliteMode::None" },
		{ "OverlayDecal.DisplayName", "Project As Decal Above Landscape" },
		{ "OverlayDecal.Name", "EMapboxSatelliteMode::OverlayDecal" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMapboxSatelliteMode::None", (int64)EMapboxSatelliteMode::None },
		{ "EMapboxSatelliteMode::BlendIntoMaterial", (int64)EMapboxSatelliteMode::BlendIntoMaterial },
		{ "EMapboxSatelliteMode::OverlayDecal", (int64)EMapboxSatelliteMode::OverlayDecal },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_MapboxLandscape,
	nullptr,
	"EMapboxSatelliteMode",
	"EMapboxSatelliteMode",
	Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode()
{
	if (!Z_Registration_Info_UEnum_EMapboxSatelliteMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMapboxSatelliteMode.InnerSingleton, Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EMapboxSatelliteMode.InnerSingleton;
}
// ********** End Enum EMapboxSatelliteMode ********************************************************

// ********** Begin ScriptStruct FMapboxLayerDef ***************************************************
struct Z_Construct_UScriptStruct_FMapboxLayerDef_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMapboxLayerDef); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMapboxLayerDef); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LayerName_MetaData[] = {
		{ "Category", "Layer" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetColor_MetaData[] = {
		{ "Category", "Color Match" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorSpace_MetaData[] = {
		{ "Category", "Color Match" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HueTolerance_MetaData[] = {
		{ "Category", "Color Match" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SatTolerance_MetaData[] = {
		{ "Category", "Color Match" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ValTolerance_MetaData[] = {
		{ "Category", "Color Match" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RGBTolerance_MetaData[] = {
		{ "Category", "Color Match" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "EditCondition", "ColorSpace == EMapboxColorSpace::RGB" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Priority_MetaData[] = {
		{ "Category", "Layer" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaterialTint_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlbedoTexture_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicalMaterial_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bScatterEnabled_MetaData[] = {
		{ "Category", "Scatter" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScatterMeshes_MetaData[] = {
		{ "Category", "Scatter" },
		{ "EditCondition", "bScatterEnabled" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScatterDensity_MetaData[] = {
		{ "Category", "Scatter" },
		{ "ClampMin", "0.0" },
		{ "EditCondition", "bScatterEnabled" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Average meshes per 100 square meters." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScatterMinScale_MetaData[] = {
		{ "Category", "Scatter" },
		{ "ClampMin", "0.0" },
		{ "EditCondition", "bScatterEnabled" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScatterMaxScale_MetaData[] = {
		{ "Category", "Scatter" },
		{ "ClampMin", "0.0" },
		{ "EditCondition", "bScatterEnabled" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRandomYaw_MetaData[] = {
		{ "Category", "Scatter" },
		{ "EditCondition", "bScatterEnabled" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAlignToLandscapeNormal_MetaData[] = {
		{ "Category", "Scatter" },
		{ "EditCondition", "bScatterEnabled" },
		{ "ModuleRelativePath", "Public/MapboxLayerDef.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMapboxLayerDef constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_LayerName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetColor;
	static const UECodeGen_Private::FBytePropertyParams NewProp_ColorSpace_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ColorSpace;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HueTolerance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SatTolerance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ValTolerance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RGBTolerance;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Priority;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MaterialTint;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_AlbedoTexture;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_PhysicalMaterial;
	static void NewProp_bScatterEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bScatterEnabled;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_ScatterMeshes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ScatterMeshes;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScatterDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScatterMinScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScatterMaxScale;
	static void NewProp_bRandomYaw_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRandomYaw;
	static void NewProp_bAlignToLandscapeNormal_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAlignToLandscapeNormal;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMapboxLayerDef constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMapboxLayerDef>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMapboxLayerDef_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMapboxLayerDef;
class UScriptStruct* FMapboxLayerDef::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMapboxLayerDef.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMapboxLayerDef.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMapboxLayerDef, (UObject*)Z_Construct_UPackage__Script_MapboxLandscape(), TEXT("MapboxLayerDef"));
	}
	return Z_Registration_Info_UScriptStruct_FMapboxLayerDef.OuterSingleton;
	}

// ********** Begin ScriptStruct FMapboxLayerDef Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_LayerName = { "LayerName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, LayerName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LayerName_MetaData), NewProp_LayerName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_TargetColor = { "TargetColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, TargetColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetColor_MetaData), NewProp_TargetColor_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ColorSpace_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ColorSpace = { "ColorSpace", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, ColorSpace), Z_Construct_UEnum_MapboxLandscape_EMapboxColorSpace, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorSpace_MetaData), NewProp_ColorSpace_MetaData) }; // 2275079036
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_HueTolerance = { "HueTolerance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, HueTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HueTolerance_MetaData), NewProp_HueTolerance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_SatTolerance = { "SatTolerance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, SatTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SatTolerance_MetaData), NewProp_SatTolerance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ValTolerance = { "ValTolerance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, ValTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ValTolerance_MetaData), NewProp_ValTolerance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_RGBTolerance = { "RGBTolerance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, RGBTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RGBTolerance_MetaData), NewProp_RGBTolerance_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_Priority = { "Priority", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, Priority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Priority_MetaData), NewProp_Priority_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_MaterialTint = { "MaterialTint", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, MaterialTint), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaterialTint_MetaData), NewProp_MaterialTint_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_AlbedoTexture = { "AlbedoTexture", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, AlbedoTexture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlbedoTexture_MetaData), NewProp_AlbedoTexture_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_PhysicalMaterial = { "PhysicalMaterial", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, PhysicalMaterial), Z_Construct_UClass_UPhysicalMaterial_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicalMaterial_MetaData), NewProp_PhysicalMaterial_MetaData) };
void Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bScatterEnabled_SetBit(void* Obj)
{
	((FMapboxLayerDef*)Obj)->bScatterEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bScatterEnabled = { "bScatterEnabled", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMapboxLayerDef), &Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bScatterEnabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bScatterEnabled_MetaData), NewProp_bScatterEnabled_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMeshes_Inner = { "ScatterMeshes", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UStaticMesh_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMeshes = { "ScatterMeshes", nullptr, (EPropertyFlags)0x0014000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, ScatterMeshes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScatterMeshes_MetaData), NewProp_ScatterMeshes_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterDensity = { "ScatterDensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, ScatterDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScatterDensity_MetaData), NewProp_ScatterDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMinScale = { "ScatterMinScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, ScatterMinScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScatterMinScale_MetaData), NewProp_ScatterMinScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMaxScale = { "ScatterMaxScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxLayerDef, ScatterMaxScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScatterMaxScale_MetaData), NewProp_ScatterMaxScale_MetaData) };
void Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bRandomYaw_SetBit(void* Obj)
{
	((FMapboxLayerDef*)Obj)->bRandomYaw = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bRandomYaw = { "bRandomYaw", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMapboxLayerDef), &Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bRandomYaw_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRandomYaw_MetaData), NewProp_bRandomYaw_MetaData) };
void Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bAlignToLandscapeNormal_SetBit(void* Obj)
{
	((FMapboxLayerDef*)Obj)->bAlignToLandscapeNormal = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bAlignToLandscapeNormal = { "bAlignToLandscapeNormal", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMapboxLayerDef), &Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bAlignToLandscapeNormal_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAlignToLandscapeNormal_MetaData), NewProp_bAlignToLandscapeNormal_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_LayerName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_TargetColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ColorSpace_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ColorSpace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_HueTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_SatTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ValTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_RGBTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_Priority,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_MaterialTint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_AlbedoTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_PhysicalMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bScatterEnabled,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMeshes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMeshes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMinScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_ScatterMaxScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bRandomYaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewProp_bAlignToLandscapeNormal,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMapboxLayerDef Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_MapboxLandscape,
	nullptr,
	&NewStructOps,
	"MapboxLayerDef",
	Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::PropPointers),
	sizeof(FMapboxLayerDef),
	alignof(FMapboxLayerDef),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMapboxLayerDef()
{
	if (!Z_Registration_Info_UScriptStruct_FMapboxLayerDef.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMapboxLayerDef.InnerSingleton, Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMapboxLayerDef.InnerSingleton);
}
// ********** End ScriptStruct FMapboxLayerDef *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h__Script_MapboxLandscape_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EMapboxColorSpace_StaticEnum, TEXT("EMapboxColorSpace"), &Z_Registration_Info_UEnum_EMapboxColorSpace, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2275079036U) },
		{ EMapboxSatelliteMode_StaticEnum, TEXT("EMapboxSatelliteMode"), &Z_Registration_Info_UEnum_EMapboxSatelliteMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1775657975U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FMapboxLayerDef::StaticStruct, Z_Construct_UScriptStruct_FMapboxLayerDef_Statics::NewStructOps, TEXT("MapboxLayerDef"),&Z_Registration_Info_UScriptStruct_FMapboxLayerDef, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMapboxLayerDef), 1586647006U) },
	};
}; // Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h__Script_MapboxLandscape_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h__Script_MapboxLandscape_3043001506{
	TEXT("/Script/MapboxLandscape"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h__Script_MapboxLandscape_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h__Script_MapboxLandscape_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h__Script_MapboxLandscape_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h__Script_MapboxLandscape_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
