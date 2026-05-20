#include "MapboxImporterEditorSubsystem.h"

#include "MapboxImporterConfig.h"

#include "Editor.h"

void UMapboxImporterEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// Create the config lazily on first access via GetConfig.
}

void UMapboxImporterEditorSubsystem::Deinitialize()
{
	Config = nullptr;
	Super::Deinitialize();
}

UMapboxImporterEditorSubsystem* UMapboxImporterEditorSubsystem::Get()
{
	return GEditor ? GEditor->GetEditorSubsystem<UMapboxImporterEditorSubsystem>() : nullptr;
}

UMapboxImporterConfig* UMapboxImporterEditorSubsystem::GetConfig()
{
	if (!Config)
	{
		Config = NewObject<UMapboxImporterConfig>(this, UMapboxImporterConfig::StaticClass(),
			TEXT("MapboxImporterConfig"), RF_Transactional);
	}
	return Config;
}
