#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "MapboxImporterEditorSubsystem.generated.h"

class UMapboxImporterConfig;

/**
 * Editor-only subsystem that owns the singleton UMapboxImporterConfig instance.
 * The Tools > Mapbox Landscape > Open Landscape Importer panel binds to that config;
 * MissionPath plugins query this subsystem to resolve the active import bbox.
 */
UCLASS()
class MAPBOXLANDSCAPE_API UMapboxImporterEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** The live importer config. Created on first access; never null after Initialize. */
	UMapboxImporterConfig* GetConfig();

	static UMapboxImporterEditorSubsystem* Get();

private:
	UPROPERTY(Transient)
	TObjectPtr<UMapboxImporterConfig> Config;
};
