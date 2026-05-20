#pragma once

#include "CoreMinimal.h"

class UMaterialInterface;
class UPCGGraphInterface;

namespace MapboxAssetGenerator
{
	// Bumped whenever the auto-generated master material's expression graph changes meaningfully.
	// Callers (e.g. "Fix Existing Materials") use this to detect stale materials.
	static constexpr int32 MasterMaterialVersion = 2;

	/**
	 * Returns the auto-generated landscape master material at /Game/MapboxLandscape/Materials/M_MapboxLandscape.
	 * @param bForceRecreate If true, recreates the material even if one already exists.
	 *                       Use this when the generator's expected graph version has changed.
	 */
	UMaterialInterface* GetOrCreateDefaultMasterMaterial(const TArray<FName>& LayerNames, bool bForceRecreate = false);
	UMaterialInterface* GetOrCreateDefaultDecalMaterial();
	UPCGGraphInterface* GetOrCreateDefaultScatterGraph();

	FString GetPluginContentDir();
	FString GetMasterMaterialAssetPath();
	FString GetDecalMaterialAssetPath();
	FString GetScatterGraphAssetPath();
}
