// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MapboxImporterEditorSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMapboxImporterEditorSubsystem() {}

// ********** Begin Cross Module References ********************************************************
EDITORSUBSYSTEM_API UClass* Z_Construct_UClass_UEditorSubsystem();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_UMapboxImporterEditorSubsystem();
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_UMapboxImporterEditorSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_MapboxLandscape();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMapboxImporterEditorSubsystem *******************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem;
UClass* UMapboxImporterEditorSubsystem::GetPrivateStaticClass()
{
	using TClass = UMapboxImporterEditorSubsystem;
	if (!Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MapboxImporterEditorSubsystem"),
			Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem.InnerSingleton,
			StaticRegisterNativesUMapboxImporterEditorSubsystem,
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
	return Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UMapboxImporterEditorSubsystem_NoRegister()
{
	return UMapboxImporterEditorSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Editor-only subsystem that owns the hidden MapboxLandscapeActor instance used by the\n * \"Tools > Mapbox Landscape > Open Importer\" panel. Centralises the lookup so we don't\n * spawn a new actor per panel-open, and provides a single point MissionPath plugins can\n * query to find the active import context.\n */" },
#endif
		{ "IncludePath", "MapboxImporterEditorSubsystem.h" },
		{ "ModuleRelativePath", "Public/MapboxImporterEditorSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Editor-only subsystem that owns the hidden MapboxLandscapeActor instance used by the\n\"Tools > Mapbox Landscape > Open Importer\" panel. Centralises the lookup so we don't\nspawn a new actor per panel-open, and provides a single point MissionPath plugins can\nquery to find the active import context." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UMapboxImporterEditorSubsystem constinit property declarations ***********
// ********** End Class UMapboxImporterEditorSubsystem constinit property declarations *************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMapboxImporterEditorSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics
UObject* (*const Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEditorSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_MapboxLandscape,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics::ClassParams = {
	&UMapboxImporterEditorSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics::Class_MetaDataParams)
};
void UMapboxImporterEditorSubsystem::StaticRegisterNativesUMapboxImporterEditorSubsystem()
{
}
UClass* Z_Construct_UClass_UMapboxImporterEditorSubsystem()
{
	if (!Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem.OuterSingleton, Z_Construct_UClass_UMapboxImporterEditorSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem.OuterSingleton;
}
UMapboxImporterEditorSubsystem::UMapboxImporterEditorSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMapboxImporterEditorSubsystem);
UMapboxImporterEditorSubsystem::~UMapboxImporterEditorSubsystem() {}
// ********** End Class UMapboxImporterEditorSubsystem *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxImporterEditorSubsystem_h__Script_MapboxLandscape_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMapboxImporterEditorSubsystem, UMapboxImporterEditorSubsystem::StaticClass, TEXT("UMapboxImporterEditorSubsystem"), &Z_Registration_Info_UClass_UMapboxImporterEditorSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMapboxImporterEditorSubsystem), 496295674U) },
	};
}; // Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxImporterEditorSubsystem_h__Script_MapboxLandscape_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxImporterEditorSubsystem_h__Script_MapboxLandscape_3012180709{
	TEXT("/Script/MapboxLandscape"),
	Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxImporterEditorSubsystem_h__Script_MapboxLandscape_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxImporterEditorSubsystem_h__Script_MapboxLandscape_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
