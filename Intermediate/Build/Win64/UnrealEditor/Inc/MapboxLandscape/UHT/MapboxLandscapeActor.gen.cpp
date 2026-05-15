// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MapboxLandscapeActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMapboxLandscapeActor() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_AMapboxLandscapeActor();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_AMapboxLandscapeActor_NoRegister();
MAPBOXLANDSCAPE_API UEnum* Z_Construct_UEnum_MapboxLandscape_ECoordinateMode();
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
		{ "ToolString.DisplayName", "Tool String (maps.ludicdrive.com)" },
		{ "ToolString.Name", "ECoordinateMode::ToolString" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECoordinateMode::BoundingBox", (int64)ECoordinateMode::BoundingBox },
		{ "ECoordinateMode::CenterRadius", (int64)ECoordinateMode::CenterRadius },
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

// ********** Begin Class AMapboxLandscapeActor Function FetchLandscape ****************************
struct Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "CallInEditor", "true" },
		{ "Category", "Mapbox Actions" },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApiKey_MetaData[] = {
		{ "Category", "Mapbox Settings" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoordinateMode_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_North_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Bounding Box Mode\n" },
#endif
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Bounding Box Mode" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_South_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_East_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_West_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::BoundingBox" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CenterLatitude_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Center & Radius Mode\n" },
#endif
		{ "EditCondition", "CoordinateMode == ECoordinateMode::CenterRadius" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Center & Radius Mode" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CenterLongitude_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::CenterRadius" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RadiusKm_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
		{ "EditCondition", "CoordinateMode == ECoordinateMode::CenterRadius" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoordinateString_MetaData[] = {
		{ "Category", "Mapbox Settings | Coordinates" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Tool String Mode\n" },
#endif
		{ "EditCondition", "CoordinateMode == ECoordinateMode::ToolString" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Tool String Mode" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZoomLevel_MetaData[] = {
		{ "Category", "Mapbox Settings" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bImportSatellite_MetaData[] = {
		{ "Category", "Mapbox Settings" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseMaterial_MetaData[] = {
		{ "Category", "Mapbox Settings" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MetadataStyleId_MetaData[] = {
		{ "Category", "Mapbox Settings" },
		{ "ModuleRelativePath", "Public/MapboxLandscapeActor.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMapboxLandscapeActor constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ApiKey;
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
	static const UECodeGen_Private::FIntPropertyParams NewProp_ZoomLevel;
	static void NewProp_bImportSatellite_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bImportSatellite;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BaseMaterial;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MetadataStyleId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AMapboxLandscapeActor constinit property declarations **********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("FetchLandscape"), .Pointer = &AMapboxLandscapeActor::execFetchLandscape },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AMapboxLandscapeActor_FetchLandscape, "FetchLandscape" }, // 2497263596
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMapboxLandscapeActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMapboxLandscapeActor_Statics

// ********** Begin Class AMapboxLandscapeActor Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ApiKey = { "ApiKey", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, ApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApiKey_MetaData), NewProp_ApiKey_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateMode = { "CoordinateMode", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CoordinateMode), Z_Construct_UEnum_MapboxLandscape_ECoordinateMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoordinateMode_MetaData), NewProp_CoordinateMode_MetaData) }; // 2452825970
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_North = { "North", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, North), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_North_MetaData), NewProp_North_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_South = { "South", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, South), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_South_MetaData), NewProp_South_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_East = { "East", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, East), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_East_MetaData), NewProp_East_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_West = { "West", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, West), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_West_MetaData), NewProp_West_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CenterLatitude = { "CenterLatitude", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CenterLatitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CenterLatitude_MetaData), NewProp_CenterLatitude_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CenterLongitude = { "CenterLongitude", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CenterLongitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CenterLongitude_MetaData), NewProp_CenterLongitude_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_RadiusKm = { "RadiusKm", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, RadiusKm), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RadiusKm_MetaData), NewProp_RadiusKm_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_CoordinateString = { "CoordinateString", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, CoordinateString), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoordinateString_MetaData), NewProp_CoordinateString_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ZoomLevel = { "ZoomLevel", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, ZoomLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZoomLevel_MetaData), NewProp_ZoomLevel_MetaData) };
void Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bImportSatellite_SetBit(void* Obj)
{
	((AMapboxLandscapeActor*)Obj)->bImportSatellite = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bImportSatellite = { "bImportSatellite", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AMapboxLandscapeActor), &Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bImportSatellite_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bImportSatellite_MetaData), NewProp_bImportSatellite_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_BaseMaterial = { "BaseMaterial", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, BaseMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseMaterial_MetaData), NewProp_BaseMaterial_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MetadataStyleId = { "MetadataStyleId", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AMapboxLandscapeActor, MetadataStyleId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MetadataStyleId_MetaData), NewProp_MetadataStyleId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AMapboxLandscapeActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ApiKey,
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
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_ZoomLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_bImportSatellite,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_BaseMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AMapboxLandscapeActor_Statics::NewProp_MetadataStyleId,
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
		{ ECoordinateMode_StaticEnum, TEXT("ECoordinateMode"), &Z_Registration_Info_UEnum_ECoordinateMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2452825970U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMapboxLandscapeActor, AMapboxLandscapeActor::StaticClass, TEXT("AMapboxLandscapeActor"), &Z_Registration_Info_UClass_AMapboxLandscapeActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMapboxLandscapeActor), 3572728476U) },
	};
}; // Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_1187725714{
	TEXT("/Script/MapboxLandscape"),
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h__Script_MapboxLandscape_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
