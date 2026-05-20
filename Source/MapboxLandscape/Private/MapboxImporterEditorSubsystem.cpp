#include "MapboxImporterEditorSubsystem.h"

#include "MapboxLandscapeActor.h"

#include "Editor.h"
#include "EngineUtils.h"
#include "Engine/World.h"

void UMapboxImporterEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMapboxImporterEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UMapboxImporterEditorSubsystem* UMapboxImporterEditorSubsystem::Get()
{
	return GEditor ? GEditor->GetEditorSubsystem<UMapboxImporterEditorSubsystem>() : nullptr;
}

AMapboxLandscapeActor* UMapboxImporterEditorSubsystem::GetOrCreateImporterActor()
{
	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	if (!World) return nullptr;

	// First, return any existing actor that's already configured.
	for (TActorIterator<AMapboxLandscapeActor> It(World); It; ++It)
	{
		return *It;
	}

	// Spawn a fresh hidden one. The actor's constructor already marks it as editor-only
	// and hidden from the scene outliner.
	FActorSpawnParameters Params;
	Params.Name = TEXT("MapboxImporter_EditorOnly");
	Params.ObjectFlags = RF_Transactional;
	AMapboxLandscapeActor* Actor = World->SpawnActor<AMapboxLandscapeActor>(
		AMapboxLandscapeActor::StaticClass(), FTransform::Identity, Params);
	if (Actor)
	{
		Actor->SetActorLabel(TEXT("Mapbox Importer (editor-only)"));
	}
	return Actor;
}
