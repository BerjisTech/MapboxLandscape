// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MapboxLandscapeSettings.h"

#ifdef MAPBOXLANDSCAPE_MapboxLandscapeSettings_generated_h
#error "MapboxLandscapeSettings.generated.h already included, missing '#pragma once' in MapboxLandscapeSettings.h"
#endif
#define MAPBOXLANDSCAPE_MapboxLandscapeSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UMapboxLandscapeSettings *************************************************
struct Z_Construct_UClass_UMapboxLandscapeSettings_Statics;
MAPBOXLANDSCAPE_API UClass* Z_Construct_UClass_UMapboxLandscapeSettings_NoRegister();

#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMapboxLandscapeSettings(); \
	friend struct ::Z_Construct_UClass_UMapboxLandscapeSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MAPBOXLANDSCAPE_API UClass* ::Z_Construct_UClass_UMapboxLandscapeSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UMapboxLandscapeSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/MapboxLandscape"), Z_Construct_UClass_UMapboxLandscapeSettings_NoRegister) \
	DECLARE_SERIALIZER(UMapboxLandscapeSettings) \
	static constexpr const TCHAR* StaticConfigName() {return TEXT("MapboxLandscape");} \



#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UMapboxLandscapeSettings(UMapboxLandscapeSettings&&) = delete; \
	UMapboxLandscapeSettings(const UMapboxLandscapeSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMapboxLandscapeSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMapboxLandscapeSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UMapboxLandscapeSettings) \
	NO_API virtual ~UMapboxLandscapeSettings();


#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h_11_PROLOG
#define FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h_14_INCLASS_NO_PURE_DECLS \
	FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UMapboxLandscapeSettings;

// ********** End Class UMapboxLandscapeSettings ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Airmuseum_Plugins_MapboxLandscape_Source_MapboxLandscape_Public_MapboxLandscapeSettings_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
