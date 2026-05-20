#include "MapboxLandscape.h"

#include "MapboxImporterPanel.h"

#include "Framework/Docking/TabManager.h"
#include "ToolMenus.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FMapboxLandscapeModule"

static const FName MapboxImporterTabName(TEXT("MapboxLandscapeImporter"));

void FMapboxLandscapeModule::StartupModule()
{
	FGlobalTabmanager::Get()
		->RegisterNomadTabSpawner(MapboxImporterTabName,
			FOnSpawnTab::CreateRaw(this, &FMapboxLandscapeModule::SpawnImporterTab))
		.SetDisplayName(LOCTEXT("ImporterTabTitle", "Mapbox Landscape Importer"))
		.SetTooltipText(LOCTEXT("ImporterTabTooltip",
			"Configure and fetch Mapbox landscape tiles. The configuration is an editor-only authoring tool and is stripped from packaged builds."))
		.SetMenuType(ETabSpawnerMenuType::Hidden); // Menu entry below already handles invocation.

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMapboxLandscapeModule::RegisterMenus));
}

void FMapboxLandscapeModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	if (FGlobalTabmanager::Get()->HasTabSpawner(MapboxImporterTabName))
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MapboxImporterTabName);
	}
}

void FMapboxLandscapeModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* ToolsMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Tools");
	if (!ToolsMenu) return;

	FToolMenuSection& Section = ToolsMenu->FindOrAddSection(
		"MapboxLandscape",
		LOCTEXT("MapboxLandscapeSection", "Mapbox Landscape"));

	Section.AddMenuEntry(
		"OpenMapboxImporter",
		LOCTEXT("OpenImporterLabel", "Open Landscape Importer"),
		LOCTEXT("OpenImporterTooltip",
			"Opens the Mapbox Landscape Importer panel. Set your area + zoom + layers, click Fetch Landscape. "
			"Spawns real ALandscape actors into the level. This authoring panel is editor-only and stripped from packaged builds."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]
		{
			FGlobalTabmanager::Get()->TryInvokeTab(MapboxImporterTabName);
		})));
}

TSharedRef<SDockTab> FMapboxLandscapeModule::SpawnImporterTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SMapboxImporterPanel)
		];
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMapboxLandscapeModule, MapboxLandscape)
