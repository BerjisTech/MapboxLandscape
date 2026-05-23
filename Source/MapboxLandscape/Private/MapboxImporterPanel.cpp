#include "MapboxImporterPanel.h"

#include "MapboxImporterEditorSubsystem.h"
#include "MapboxImporterConfig.h"
#include "MapboxLandscapeSettings.h"

#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"

#include "HAL/PlatformProcess.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "MapboxImporterPanel"

namespace
{
	// Hosted-docs and TOS links. Kept here (rather than hardcoded in the lambdas) so
	// search-and-replace catches them if the URLs change. DocsURL matches the value
	// in MapboxLandscape.uplugin for consistency.
	static const TCHAR* MapboxTosUrl  = TEXT("https://www.mapbox.com/legal/tos");
	static const TCHAR* PluginDocsUrl = TEXT("https://github.com/BerjisTech/MapboxLandscape/tree/master/wiki");
}

void SMapboxImporterPanel::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs Args;
	Args.bAllowSearch = true;
	Args.bShowOptions = false;
	Args.bShowPropertyMatrixButton = false;
	Args.bShowObjectLabel = false;
	Args.bHideSelectionTip = true;
	Args.NameAreaSettings = FDetailsViewArgs::ObjectsUseNameArea;
	DetailsView = PropertyEditor.CreateDetailView(Args);

	ChildSlot
	[
		SNew(SVerticalBox)

		// Header
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(8.f, 8.f, 8.f, 4.f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryTop"))
			.Padding(8.f)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
					.Text(LOCTEXT("Title", "Mapbox Landscape Importer"))
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 4.f, 0.f, 0.f)
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Text(LOCTEXT("Subtitle",
						"Configure the import below and click Fetch Landscape. Defaults come from Project Settings > Plugins > Mapbox Landscape."))
				]
			]
		]

		// Mapbox TOS acknowledgement banner. Visible until the user clicks "I understand";
		// the click persists `bAcceptedMapboxTerms` to DefaultMapboxLandscape.ini and the
		// banner is removed on the next panel refresh / restart. The visibility binding
		// uses the live settings value so accepting from another part of the editor (or
		// editing the ini directly) hides it without needing to reopen the tab.
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(8.f, 0.f, 8.f, 4.f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("DetailsView.CategoryMiddle"))
			.Padding(8.f)
			.Visibility_Lambda([]() -> EVisibility
			{
				const UMapboxLandscapeSettings* S = UMapboxLandscapeSettings::Get();
				return (S && S->bAcceptedMapboxTerms) ? EVisibility::Collapsed : EVisibility::Visible;
			})
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(STextBlock)
					.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
					.Text(LOCTEXT("TosTitle", "Before you fetch — Mapbox Terms of Service"))
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 4.f, 0.f, 8.f)
				[
					SNew(STextBlock)
					.AutoWrapText(true)
					.Text(LOCTEXT("TosBody",
						"This plugin downloads data from Mapbox under YOUR Mapbox account. Geometry baked from terrain tiles is generally fine to ship; satellite imagery baked into a commercial product needs a Mapbox commercial agreement. Any output you ship must visibly credit © Mapbox © OpenStreetMap (the plugin stamps an attribution tag on every spawned landscape actor as a starting point). Read the full terms before you build a commercial project on this data."))
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(SUniformGridPanel)
					.SlotPadding(FMargin(4.f, 0.f, 0.f, 0.f))
					+ SUniformGridPanel::Slot(0, 0)
					[
						SNew(SButton)
						.Text(LOCTEXT("TosOpen", "Read Mapbox Terms"))
						.OnClicked_Lambda([]() -> FReply
						{
							FPlatformProcess::LaunchURL(MapboxTosUrl, nullptr, nullptr);
							return FReply::Handled();
						})
					]
					+ SUniformGridPanel::Slot(1, 0)
					[
						SNew(SButton)
						.Text(LOCTEXT("TosAccept", "I understand"))
						.OnClicked_Lambda([]() -> FReply
						{
							if (UMapboxLandscapeSettings* S = GetMutableDefault<UMapboxLandscapeSettings>())
							{
								S->bAcceptedMapboxTerms = true;
								S->SaveConfig();
							}
							return FReply::Handled();
						})
					]
				]
			]
		]

		// Help button row. Lives above the DetailsView so it's reachable without scrolling
		// the (long) settings list. Opens DocsURL in the user's browser.
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(8.f, 0.f, 8.f, 4.f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(1.f)
			+ SHorizontalBox::Slot().AutoWidth()
			[
				SNew(SButton)
				.ToolTipText(LOCTEXT("HelpTooltip", "Open the plugin documentation in your browser."))
				.Text(LOCTEXT("Help", "Help / Docs"))
				.OnClicked_Lambda([]() -> FReply
				{
					FPlatformProcess::LaunchURL(PluginDocsUrl, nullptr, nullptr);
					return FReply::Handled();
				})
			]
		]

		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		.Padding(8.f, 4.f, 8.f, 8.f)
		[
			DetailsView.ToSharedRef()
		]
	];

	RefreshTarget();
}

void SMapboxImporterPanel::RefreshTarget()
{
	if (!DetailsView.IsValid()) return;
	if (UMapboxImporterEditorSubsystem* Sub = UMapboxImporterEditorSubsystem::Get())
	{
		if (UMapboxImporterConfig* Cfg = Sub->GetConfig())
		{
			DetailsView->SetObject(Cfg, /*bForceRefresh=*/true);
			return;
		}
	}
	DetailsView->SetObject(nullptr);
}

#undef LOCTEXT_NAMESPACE
