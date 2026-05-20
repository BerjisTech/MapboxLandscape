#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class IDetailsView;
class AMapboxLandscapeActor;

/**
 * Slate panel hosted in the "Tools > Mapbox Landscape > Open Importer" dockable tab.
 * Embeds an IDetailsView bound to the editor subsystem's hidden importer actor.
 */
class SMapboxImporterPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMapboxImporterPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	// Re-binds the details view to the current editor world's importer actor.
	void RefreshTarget();

private:
	TSharedPtr<IDetailsView> DetailsView;
};
