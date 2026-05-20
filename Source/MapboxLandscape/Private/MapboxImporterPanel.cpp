#include "MapboxImporterPanel.h"

#include "MapboxImporterEditorSubsystem.h"
#include "MapboxLandscapeActor.h"

#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"

#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "MapboxImporterPanel"

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
		AMapboxLandscapeActor* Actor = Sub->GetOrCreateImporterActor();
		if (Actor)
		{
			DetailsView->SetObject(Actor, /*bForceRefresh=*/true);
			return;
		}
	}
	DetailsView->SetObject(nullptr);
}

#undef LOCTEXT_NAMESPACE
