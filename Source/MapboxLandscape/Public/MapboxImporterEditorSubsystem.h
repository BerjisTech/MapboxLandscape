#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "MapboxImporterEditorSubsystem.generated.h"

class AMapboxLandscapeActor;
class UWorld;

/**
 * Editor-only subsystem that owns the hidden MapboxLandscapeActor instance used by the
 * "Tools > Mapbox Landscape > Open Importer" panel. Centralises the lookup so we don't
 * spawn a new actor per panel-open, and provides a single point MissionPath plugins can
 * query to find the active import context.
 */
UCLASS()
class MAPBOXLANDSCAPE_API UMapboxImporterEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Returns the hidden importer actor for the current editor world. Creates one if needed. */
	AMapboxLandscapeActor* GetOrCreateImporterActor();

	static UMapboxImporterEditorSubsystem* Get();
};
