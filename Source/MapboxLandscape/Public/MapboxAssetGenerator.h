#pragma once

#include "CoreMinimal.h"

class UMaterialInterface;
class UPCGGraphInterface;

namespace MapboxAssetGenerator
{
	UMaterialInterface* GetOrCreateDefaultMasterMaterial(const TArray<FName>& LayerNames);
	UMaterialInterface* GetOrCreateDefaultDecalMaterial();
	UPCGGraphInterface* GetOrCreateDefaultScatterGraph();

	FString GetPluginContentDir();
	FString GetMasterMaterialAssetPath();
	FString GetDecalMaterialAssetPath();
	FString GetScatterGraphAssetPath();
}
