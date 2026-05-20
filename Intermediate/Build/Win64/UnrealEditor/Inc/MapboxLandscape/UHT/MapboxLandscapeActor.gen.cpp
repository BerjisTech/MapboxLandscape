// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MapboxLandscapeActor.h"
#include "MapboxLayerDef.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMapboxLandscapeActor() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
LANDSCAPE_API UClass* Z_Construct_UClass_ALandscape_NoRegister();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_AMapboxLandscapeActor();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_AMapboxLandscapeActor_NoRegister();
MAPBOXLANDSCAPE_API UEnum* Z_Construct_UEnum_MapboxLandscape_ECoordinateMode();
MAPBOXLANDSCAPE_API UEnum* Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode();
MAPBOXLANDSCAPE_API UScriptStruct* Z_Construct_UScriptStruct_FMapboxLayerDef();
MAPBOXLANDSCAPE_API UScriptStruct* Z_Construct_UScriptStruct_FMapboxTileResult();
PCG_API UClass* Z_Construct_UClass_UPCGGraphInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_MapboxLandscape();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum ECoordinateMode ***********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECoordinateMode;
static UEnum* ECoordinateMode_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ECoordinateMode.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ECoordinateMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_MapboxLandscape_ECoordinateMode, (UObject*)Z_Construct_UPackage__Script_MapboxLandscape(), TEXT("ECoordinateMode"));
	}
	return Z_Registration_Info_UEnum_ECoordinateMode.OuterSingleton;
}
template<> MAPBOXLANDSCAPE_NON_ATTRIBUTED_API UEnum* StaticEnum<ECoordinateMode>()
{
	return ECoordinateMode_StaticEnum();
}
struct Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "BoundingBox.DisplayName", "Bounding Box (N/S/E/W)" },
		{ "BoundingBox.Name", "ECoordinateMode::BoundingBox" },
		{ "CenterRadius.DisplayName", "Center Point & Radius" },
		{ "CenterRadius.Name", "ECoordinateMode::CenterRadius" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
		{ "ToolString.DisplayName", "Tool String (comma-separated lat/lng)" },
		{ "ToolString.Name", "ECoordinateMode::ToolString" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECoordinateMode::CenterRadius", (int64)ECoordinateMode::CenterRadius },
		{ "ECoordinateMode::BoundingBox", (int64)ECoordinateMode::BoundingBox },
		{ "ECoordinateMode::ToolString", (int64)ECoordinateMode::ToolString },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_MapboxLandscape,
	nullptr,
	"ECoordinateMode",
	"ECoordinateMode",
	Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics::Enum_MetaDataParams), Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_MapboxLandscape_ECoordinateMode()
{
	if (!Z_Registration_Info_UEnum_ECoordinateMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECoordinateMode.InnerSingleton, Z_Construct_UEnum_MapboxLandscape_ECoordinateMode_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ECoordinateMode.InnerSingleton;
}
// ********** End Enum ECoordinateMode *************************************************************

// ********** Begin ScriptStruct FMapboxTileResult *************************************************
struct Z_Construct_UScriptStruct_FMapboxTileResult_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMapboxTileResult); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMapboxTileResult); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileGridX_MetaData[] = {
		{ "Category", "Tile" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TileGridY_MetaData[] = {
		{ "Category", "Tile" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Landscape_MetaData[] = {
		{ "Category", "Tile" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMapboxTileResult constinit property declarations *****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_TileGridX;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TileGridY;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Landscape;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMapboxTileResult constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMapboxTileResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMapboxTileResult_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMapboxTileResult;
class UScriptStruct* FMapboxTileResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMapboxTileResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMapboxTileResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMapboxTileResult, (UObject*)Z_Construct_UPackage__Script_MapboxLandscape(), TEXT("MapboxTileResult"));
	}
	return Z_Registration_Info_UScriptStruct_FMapboxTileResult.OuterSingleton;
	}

// ********** Begin ScriptStruct FMapboxTileResult Property Definitions ****************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMapboxTileResult_Statics::NewProp_TileGridX = { "TileGridX", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxTileResult, TileGridX), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileGridX_MetaData), NewProp_TileGridX_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FMapboxTileResult_Statics::NewProp_TileGridY = { "TileGridY", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxTileResult, TileGridY), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TileGridY_MetaData), NewProp_TileGridY_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FMapboxTileResult_Statics::NewProp_Landscape = { "Landscape", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapboxTileResult, Landscape), Z_Construct_UClass_ALandscape_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Landscape_MetaData), NewProp_Landscape_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMapboxTileResult_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxTileResult_Statics::NewProp_TileGridX,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxTileResult_Statics::NewProp_TileGridY,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapboxTileResult_Statics::NewProp_Landscape,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapboxTileResult_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMapboxTileResult Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMapboxTileResult_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_MapboxLandscape,
	nullptr,
	&NewStructOps,
	"MapboxTileResult",
	Z_Construct_UScriptStruct_FMapboxTileResult_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapboxTileResult_Statics::PropPointers),
	sizeof(FMapboxTileResult),
	alignof(FMapboxTileResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapboxTileResult_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMapboxTileResult_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMapboxTileResult()
{
	if (!Z_Registration_Info_UScriptStruct_FMapboxTileResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMapboxTileResult.InnerSingleton, Z_Construct_UScriptStruct_FMapboxTileResult_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMapboxTileResult.InnerSingleton);
}
// ********** End ScriptStruct FMapboxTileResult ***************************************************

// ********** Begin Class AMapboxLandscapeActor Function ClearGeneratedLandscapes ******************
struct Z_Construct_UFunction_AMapboxLandscapeActor_ClearGeneratedLandscapes_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Mapbox|Actions" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClearGeneratedLandscapes constinit property declarations **************
// ********** End Function ClearGeneratedLandscapes constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapboxLandscapeActor_ClearGeneratedLandscapes_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapboxLandscapeActor, nullptr, "ClearGeneratedLandscapes", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapboxLandscapeActor_ClearGeneratedLandscapes_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapboxLandscapeActor_ClearGeneratedLandscapes_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMapboxLandscapeActor_ClearGeneratedLandscapes()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapboxLandscapeActor_ClearGeneratedLandscapes_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapboxLandscapeActor::execClearGeneratedLandscapes)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearGeneratedLandscapes();
	P_NATIVE_END;
}
// ********** End Class AMapboxLandscapeActor Function ClearGeneratedLandscapes ********************

// ********** Begin Class AMapboxLandscapeActor Function FetchLandscape ****************************
struct Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Mapbox|Actions" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function FetchLandscape constinit property declarations ************************
// ********** End Function FetchLandscape constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapboxLandscapeActor, nullptr, "FetchLandscape", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapboxLandscapeActor::execFetchLandscape)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->FetchLandscape();
	P_NATIVE_END;
}
// ********** End Class AMapboxLandscapeActor Function FetchLandscape ******************************

// ********** Begin Class AMapboxLandscapeActor Function RegenerateDefaultAssets *******************
struct Z_Construct_UFunction_AMapboxLandscapeActor_RegenerateDefaultAssets_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Mapbox|Actions" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Force regeneration of the default M_MapboxLandscape material and PCG scatter graph in the plugin's Content folder." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RegenerateDefaultAssets constinit property declarations ***************
// ********** End Function RegenerateDefaultAssets constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapboxLandscapeActor_RegenerateDefaultAssets_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapboxLandscapeActor, nullptr, "RegenerateDefaultAssets", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapboxLandscapeActor_RegenerateDefaultAssets_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapboxLandscapeActor_RegenerateDefaultAssets_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMapboxLandscapeActor_RegenerateDefaultAssets()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapboxLandscapeActor_RegenerateDefaultAssets_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapboxLandscapeActor::execRegenerateDefaultAssets)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegenerateDefaultAssets();
	P_NATIVE_END;
}
// ********** End Class AMapboxLandscapeActor Function RegenerateDefaultAssets *********************

// ********** Begin Class AMapboxLandscapeActor Function ResetFromProjectSettings ******************
struct Z_Construct_UFunction_AMapboxLandscapeActor_ResetFromProjectSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Mapbox|Actions" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Copy the current project settings (zoom, layers, material, etc.) into this actor, overwriting any per-actor overrides." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetFromProjectSettings constinit property declarations **************
// ********** End Function ResetFromProjectSettings constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapboxLandscapeActor_ResetFromProjectSettings_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapboxLandscapeActor, nullptr, "ResetFromProjectSettings", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapboxLandscapeActor_ResetFromProjectSettings_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapboxLandscapeActor_ResetFromProjectSettings_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMapboxLandscapeActor_ResetFromProjectSettings()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapboxLandscapeActor_ResetFromProjectSettings_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapboxLandscapeActor::execResetFromProjectSettings)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetFromProjectSettings();
	P_NATIVE_END;
}
// ********** End Class AMapboxLandscapeActor Function ResetFromProjectSettings ********************

// ********** Begin Class AMapboxLandscapeActor Function ResetLayersToDefaults *********************
struct Z_Construct_UFunction_AMapboxLandscapeActor_ResetLayersToDefaults_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Mapbox|Actions" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ResetLayersToDefaults constinit property declarations *****************
// ********** End Function ResetLayersToDefaults constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AMapboxLandscapeActor_ResetLayersToDefaults_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_AMapboxLandscapeActor, nullptr, "ResetLayersToDefaults", 	nullptr, 
	0, 
0,
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AMapboxLandscapeActor_ResetLayersToDefaults_Statics::Function_MetaDataParams), Z_Construct_UFunction_AMapboxLandscapeActor_ResetLayersToDefaults_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_AMapboxLandscapeActor_ResetLayersToDefaults()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AMapboxLandscapeActor_ResetLayersToDefaults_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AMapboxLandscapeActor::execResetLayersToDefaults)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetLayersToDefaults();
	P_NATIVE_END;
}
// ********** End Class AMapboxLandscapeActor Function ResetLayersToDefaults ***********************

// ********** Begin Class AMapboxLandscapeActor ****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMapboxLandscapeActor;
UClass* AMapboxLandscapeActor::GetPrivateStaticClass()
{
	using TClass = AMapboxLandscapeActor;
	if (!Z_Registration_Info_UClass_AMapboxLandscapeActor.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MapboxLandscapeActor"),
			Z_Registration_Info_UClass_AMapboxLandscapeActor.InnerSingleton,
			StaticRegisterNativesAMapboxLandscapeActor,
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
	return Z_Registration_Info_UClass_AMapboxLandscapeActor.InnerSingleton;
}
UClass* Z_Construct_UClass_AMapboxLandscapeActor_NoRegister()
{
	return AMapboxLandscapeActor::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMapboxLandscapeActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MapboxLandscapeActor.h" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoordinateMode_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_North_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_South_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_East_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_West_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CenterLatitude_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::CenterRadius" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CenterLongitude_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::CenterRadius" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RadiusKm_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "ClampMax", "200.0" },
		{ "ClampMin", "0.1" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::CenterRadius" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoordinateString_MetaData[] = {
		{ "Category", "Mapbox|Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::ToolString" },
		{ "EditConditionHides", "" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoZoom_MetaData[] = {
		{ "Category", "Mapbox|Tiling" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZoomLevel_MetaData[] = {
		{ "Category", "Mapbox|Tiling" },
		{ "ClampMax", "18" },
		{ "ClampMin", "8" },
		{ "EditCondition", "!bAutoZoom" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TilesPerLandscapeSide_MetaData[] = {
		{ "Category", "Mapbox|Tiling" },
		{ "ClampMax", "16" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Web-mercator tiles grouped together into one ALandscape. 4 -> 1024px landscapes. Lower = more landscapes, higher fidelity per actor." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxLandscapesTotal_MetaData[] = {
		{ "Category", "Mapbox|Tiling" },
		{ "ClampMax", "256" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Hard cap so a typo doesn't request thousands of tiles." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxConcurrentRequests_MetaData[] = {
		{ "Category", "Mapbox|Tiling" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MetersPerPixel_MetaData[] = {
		{ "Category", "Mapbox|Tiling" },
		{ "ClampMax", "1000.0" },
		{ "ClampMin", "1.0" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cell size in cm per heightmap sample. 100 = 1m per pixel." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZExaggeration_MetaData[] = {
		{ "Category", "Mapbox|Elevation" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.1" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRebaseToSeaLevel_MetaData[] = {
		{ "Category", "Mapbox|Elevation" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SatelliteMode_MetaData[] = {
		{ "Category", "Mapbox|Satellite" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MetadataStyleId_MetaData[] = {
		{ "Category", "Mapbox|Style" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mapbox style used to derive the layer classification. Pick a style with solid colors per land type." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MapboxLayers_MetaData[] = {
		{ "Category", "Mapbox|Layers" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LandscapeMasterMaterial_MetaData[] = {
		{ "Category", "Mapbox|Material" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Master landscape material. Leave empty to auto-generate the default M_MapboxLandscape on Fetch." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoGenerateDefaultAssets_MetaData[] = {
		{ "Category", "Mapbox|Material" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScatterPCGGraph_MetaData[] = {
		{ "Category", "Mapbox|PCG" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PCG graph spawned on each landscape to scatter the per-layer assets. Auto-generated if empty." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSpawnPCGComponents_MetaData[] = {
		{ "Category", "Mapbox|PCG" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GeneratedLandscapes_MetaData[] = {
		{ "Category", "Mapbox|Status" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMapboxLandscapeActor constinit property declarations ********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_CoordinateMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CoordinateMode;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_North;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_South;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_East;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_West;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_CenterLatitude;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_CenterLongitude;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_RadiusKm;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CoordinateString;
	static void NewProp_bAutoZoom_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoZoom;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ZoomLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TilesPerLandscapeSide;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxLandscapesTotal;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxConcurrentRequests;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MetersPerPixel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ZExaggeration;
	static void NewProp_bRebaseToSeaLevel_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRebaseToSeaLevel;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SatelliteMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SatelliteMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MetadataStyleId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MapboxLayers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MapboxLayers;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_LandscapeMasterMaterial;
	static void NewProp_bAutoGenerateDefaultAssets_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoGenerateDefaultAssets;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_ScatterPCGGraph;
	static void NewProp_bSpawnPCGComponents_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSpawnPCGComponents;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GeneratedLandscapes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_GeneratedLandscapes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMapboxLandscapeActor constinit property declarations **********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClearGeneratedLandscapes"), .Pointer = &AMapboxLandscapeActor::execClearGeneratedLandscapes },
		{ .NameUTF8 = UTF8TEXT("FetchLandscape"), .Pointer = &AMapboxLandscapeActor::execFetchLandscape },
		{ .NameUTF8 = UTF8TEXT("RegenerateDefaultAssets"), .Pointer = &AMapboxLandscapeActor::execRegenerateDefaultAssets },
		{ .NameUTF8 = UTF8TEXT("ResetFromProjectSettings"), .Pointer = &AMapboxLandscapeActor::execResetFromProjectSettings },
		{ .NameUTF8 = UTF8TEXT("ResetLayersToDefaults"), .Pointer = &AMapboxLandscapeActor::execResetLayersToDefaults },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMapboxLandscapeActor_ClearGeneratedLandscapes, "ClearGeneratedLandscapes" }, // 677022258
		{ &Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape, "FetchLandscape" }, // 439468427
		{ &Z_Construct_UFunction_AMapboxLandscapeActor_RegenerateDefaultAssets, "RegenerateDefaultAssets" }, // 1469538535
		{ &Z_Construct_UFunction_AMapboxLandscapeActor_ResetFromProjectSettings, "ResetFromProjectSettings" }, // 1092985318
		{ &Z_Construct_UFunction_AMapboxLandscapeActor_ResetLayersToDefaults, "ResetLayersToDefaults" }, // 1333620503
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMapboxLandscapeActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMapboxLandscapeActor_Statics

// ********** Begin Class AMapboxLandscapeActor Property Definitions *******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateMode = { "CoordinateMode", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CoordinateMode), Z_Construct_UEnum_MapboxLandscape_ECoordinateMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoordinateMode_MetaData), NewProp_CoordinateMode_MetaData) }; // 406660137
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_North = { "North", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, North), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_North_MetaData), NewProp_North_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_South = { "South", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, South), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_South_MetaData), NewProp_South_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_East = { "East", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, East), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_East_MetaData), NewProp_East_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_West = { "West", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, West), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_West_MetaData), NewProp_West_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CenterLatitude = { "CenterLatitude", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CenterLatitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CenterLatitude_MetaData), NewProp_CenterLatitude_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CenterLongitude = { "CenterLongitude", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CenterLongitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CenterLongitude_MetaData), NewProp_CenterLongitude_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_RadiusKm = { "RadiusKm", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, RadiusKm), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RadiusKm_MetaData), NewProp_RadiusKm_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateString = { "CoordinateString", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CoordinateString), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoordinateString_MetaData), NewProp_CoordinateString_MetaData) };
void Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoZoom_SetBit(void* Obj)
{
	((AMapboxLandscapeActor*)Obj)->bAutoZoom = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoZoom = { "bAutoZoom", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMapboxLandscapeActor), &Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoZoom_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoZoom_MetaData), NewProp_bAutoZoom_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ZoomLevel = { "ZoomLevel", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, ZoomLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZoomLevel_MetaData), NewProp_ZoomLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_TilesPerLandscapeSide = { "TilesPerLandscapeSide", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, TilesPerLandscapeSide), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TilesPerLandscapeSide_MetaData), NewProp_TilesPerLandscapeSide_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MaxLandscapesTotal = { "MaxLandscapesTotal", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, MaxLandscapesTotal), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxLandscapesTotal_MetaData), NewProp_MaxLandscapesTotal_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MaxConcurrentRequests = { "MaxConcurrentRequests", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, MaxConcurrentRequests), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxConcurrentRequests_MetaData), NewProp_MaxConcurrentRequests_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MetersPerPixel = { "MetersPerPixel", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, MetersPerPixel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MetersPerPixel_MetaData), NewProp_MetersPerPixel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ZExaggeration = { "ZExaggeration", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, ZExaggeration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZExaggeration_MetaData), NewProp_ZExaggeration_MetaData) };
void Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bRebaseToSeaLevel_SetBit(void* Obj)
{
	((AMapboxLandscapeActor*)Obj)->bRebaseToSeaLevel = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bRebaseToSeaLevel = { "bRebaseToSeaLevel", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMapboxLandscapeActor), &Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bRebaseToSeaLevel_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRebaseToSeaLevel_MetaData), NewProp_bRebaseToSeaLevel_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_SatelliteMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_SatelliteMode = { "SatelliteMode", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, SatelliteMode), Z_Construct_UEnum_MapboxLandscape_EMapboxSatelliteMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SatelliteMode_MetaData), NewProp_SatelliteMode_MetaData) }; // 1775657975
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MetadataStyleId = { "MetadataStyleId", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, MetadataStyleId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MetadataStyleId_MetaData), NewProp_MetadataStyleId_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MapboxLayers_Inner = { "MapboxLayers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMapboxLayerDef, METADATA_PARAMS(0, nullptr) }; // 1586647006
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MapboxLayers = { "MapboxLayers", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, MapboxLayers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MapboxLayers_MetaData), NewProp_MapboxLayers_MetaData) }; // 1586647006
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_LandscapeMasterMaterial = { "LandscapeMasterMaterial", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, LandscapeMasterMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LandscapeMasterMaterial_MetaData), NewProp_LandscapeMasterMaterial_MetaData) };
void Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoGenerateDefaultAssets_SetBit(void* Obj)
{
	((AMapboxLandscapeActor*)Obj)->bAutoGenerateDefaultAssets = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoGenerateDefaultAssets = { "bAutoGenerateDefaultAssets", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMapboxLandscapeActor), &Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoGenerateDefaultAssets_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoGenerateDefaultAssets_MetaData), NewProp_bAutoGenerateDefaultAssets_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ScatterPCGGraph = { "ScatterPCGGraph", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::SoftObject, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, ScatterPCGGraph), Z_Construct_UClass_UPCGGraphInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScatterPCGGraph_MetaData), NewProp_ScatterPCGGraph_MetaData) };
void Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bSpawnPCGComponents_SetBit(void* Obj)
{
	((AMapboxLandscapeActor*)Obj)->bSpawnPCGComponents = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bSpawnPCGComponents = { "bSpawnPCGComponents", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMapboxLandscapeActor), &Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bSpawnPCGComponents_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSpawnPCGComponents_MetaData), NewProp_bSpawnPCGComponents_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_GeneratedLandscapes_Inner = { "GeneratedLandscapes", nullptr, (EPropertyFlags)0x0000000000020000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMapboxTileResult, METADATA_PARAMS(0, nullptr) }; // 4136422788
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_GeneratedLandscapes = { "GeneratedLandscapes", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, GeneratedLandscapes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GeneratedLandscapes_MetaData), NewProp_GeneratedLandscapes_MetaData) }; // 4136422788
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMapboxLandscapeActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_North,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_South,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_East,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_West,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CenterLatitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CenterLongitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_RadiusKm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateString,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoZoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ZoomLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_TilesPerLandscapeSide,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MaxLandscapesTotal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MaxConcurrentRequests,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MetersPerPixel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ZExaggeration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bRebaseToSeaLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_SatelliteMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_SatelliteMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MetadataStyleId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MapboxLayers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MapboxLayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_LandscapeMasterMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bAutoGenerateDefaultAssets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ScatterPCGGraph,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bSpawnPCGComponents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_GeneratedLandscapes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_GeneratedLandscapes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMapboxLandscapeActor_Statics::PropPointers) < 2048);
// ********** End Class AMapboxLandscapeActor Property Definitions *********************************
UObject* (*const Z_Construct_UClass_AMapboxLandscapeActor_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_MapboxLandscape,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMapboxLandscapeActor_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::ClassParams = {
	&AMapboxLandscapeActor::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AMapboxLandscapeActor_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AMapboxLandscapeActor_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMapboxLandscapeActor_Statics::Class_MetaDataParams), Z_Construct_UClass_AMapboxLandscapeActor_Statics::Class_MetaDataParams)
};
void AMapboxLandscapeActor::StaticRegisterNativesAMapboxLandscapeActor()
{
	UClass* Class = AMapboxLandscapeActor::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_AMapboxLandscapeActor_Statics::Funcs));
}
UClass* Z_Construct_UClass_AMapboxLandscapeActor()
{
	if (!Z_Registration_Info_UClass_AMapboxLandscapeActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMapboxLandscapeActor.OuterSingleton, Z_Construct_UClass_AMapboxLandscapeActor_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMapboxLandscapeActor.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMapboxLandscapeActor);
AMapboxLandscapeActor::~AMapboxLandscapeActor() {}
// ********** End Class AMapboxLandscapeActor ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ECoordinateMode_StaticEnum, TEXT("ECoordinateMode"), &Z_Registration_Info_UEnum_ECoordinateMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 406660137U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FMapboxTileResult::StaticStruct, Z_Construct_UScriptStruct_FMapboxTileResult_Statics::NewStructOps, TEXT("MapboxTileResult"),&Z_Registration_Info_UScriptStruct_FMapboxTileResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMapboxTileResult), 4136422788U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMapboxLandscapeActor, AMapboxLandscapeActor::StaticClass, TEXT("AMapboxLandscapeActor"), &Z_Registration_Info_UClass_AMapboxLandscapeActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMapboxLandscapeActor), 3243674545U) },
	};
}; // Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_2391632897{
	TEXT("/Script/MapboxLandscape"),
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
