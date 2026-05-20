// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MapboxLandscapeActor.h"

#ifdef MAPBOXLANDSCAPE_MapboxLandscapeActor_generated_h
#error "MapboxLandscapeActor.generated.h already included, missing '#pragma once' in MapboxLandscapeActor.h"
#endif
#define MAPBOXLANDSCAPE_MapboxLandscapeActor_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FMapboxTileResult *************************************************
struct Z_Construct_UScriptStruct_FMapboxTileResult_Statics;
#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_25_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FMapboxTileResult_Statics; \
	MAPBOXLANDSCAPE_API static class UScriptStruct* StaticStruct();


struct FMapboxTileResult;
// ********** End ScriptStruct FMapboxTileResult ***************************************************

// ********** Begin Class AMapboxLandscapeActor ****************************************************
#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_40_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execResetFromProjectSettings); \
	DECLARE_FUNCTION(execRegenerateDefaultAssets); \
	DECLARE_FUNCTION(execResetLayersToDefaults); \
	DECLARE_FUNCTION(execClearGeneratedLandscapes); \
	DECLARE_FUNCTION(execFetchLandscape);


struct Z_Construct_UClass_AMapboxLandscapeActor_Statics;
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_AMapboxLandscapeActor_NoRegister();

#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_40_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMapboxLandscapeActor(); \
	friend struct ::Z_Construct_UClass_AMapboxLandscapeActor_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MAPBOXLANDSCAPE_API UClass* ::Z_Construct_UClass_AMapboxLandscapeActor_NoRegister(); \
public: \
	DECLARE_CLASS2(AMapboxLandscapeActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MapboxLandscape"), Z_Construct_UClass_AMapboxLandscapeActor_NoRegister) \
	DECLARE_SERIALIZER(AMapboxLandscapeActor)


#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_40_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMapboxLandscapeActor(AMapboxLandscapeActor&&) = delete; \
	AMapboxLandscapeActor(const AMapboxLandscapeActor&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMapboxLandscapeActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMapboxLandscapeActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMapboxLandscapeActor) \
	NO_API virtual ~AMapboxLandscapeActor();


#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_37_PROLOG
#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_40_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_40_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_40_INCLASS_NO_PURE_DECLS \
	FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h_40_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMapboxLandscapeActor;

// ********** End Class AMapboxLandscapeActor ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeActor_h

// ********** Begin Enum ECoordinateMode ***********************************************************
#define FOREACH_ENUM_ECOORDINATEMODE(op) \
	op(ECoordinateMode::CenterRadius) \
	op(ECoordinateMode::BoundingBox) \
	op(ECoordinateMode::ToolString) 

enum class ECoordinateMode : uint8;
template<> struct TIsUEnumClass<ECoordinateMode> { enum { Value = true }; };
template<> MAPBOXLANDSCAPE_NON_ATTRIBUTED_API UEnum* StaticEnum<ECoordinateMode>();
// ********** End Enum ECoordinateMode *************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
