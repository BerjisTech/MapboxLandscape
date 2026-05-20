// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MapboxLayerDef.h"

#ifdef MAPBOXLANDSCAPE_MapboxLayerDef_generated_h
#error "MapboxLayerDef.generated.h already included, missing '#pragma once' in MapboxLayerDef.h"
#endif
#define MAPBOXLANDSCAPE_MapboxLayerDef_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FMapboxLayerDef ***************************************************
struct Z_Construct_UScriptStruct_FMapboxLayerDef_Statics;
#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h_26_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FMapboxLayerDef_Statics; \
	MAPBOXLANDSCAPE_API static class UScriptStruct* StaticStruct();


struct FMapboxLayerDef;
// ********** End ScriptStruct FMapboxLayerDef *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLayerDef_h

// ********** Begin Enum EMapboxColorSpace *********************************************************
#define FOREACH_ENUM_EMAPBOXCOLORSPACE(op) \
	op(EMapboxColorSpace::RGB) \
	op(EMapboxColorSpace::HSV) 

enum class EMapboxColorSpace : uint8;
template<> struct TIsUEnumClass<EMapboxColorSpace> { enum { Value = true }; };
template<> MAPBOXLANDSCAPE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMapboxColorSpace>();
// ********** End Enum EMapboxColorSpace ***********************************************************

// ********** Begin Enum EMapboxSatelliteMode ******************************************************
#define FOREACH_ENUM_EMAPBOXSATELLITEMODE(op) \
	op(EMapboxSatelliteMode::None) \
	op(EMapboxSatelliteMode::BlendIntoMaterial) \
	op(EMapboxSatelliteMode::OverlayDecal) 

enum class EMapboxSatelliteMode : uint8;
template<> struct TIsUEnumClass<EMapboxSatelliteMode> { enum { Value = true }; };
template<> MAPBOXLANDSCAPE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMapboxSatelliteMode>();
// ********** End Enum EMapboxSatelliteMode ********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
