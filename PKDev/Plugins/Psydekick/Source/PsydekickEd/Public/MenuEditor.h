#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MenuEditorWidget.h"

class IDetailsView;
class SDockableTab;
class UMenu;

class PSYDEKICKED_API FMenuEditor : public FAssetEditorToolkit
{
public:
	void InitMenuEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UMenu* InMenu);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	/** Destructor */
	virtual ~FMenuEditor();

	/** Begin IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }
	/** End IToolkit interface */

	static const FName ToolkitFName;
	static const FName PropertiesTabId;
	static const FName MenuEditTabId;
	static const FName MenuEditorAppIdentifier;

private:

	UObject* LoadAssetFromContent(FString Path);

	/** Create the properties tab and its content */
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnMenuEditTab(const FSpawnTabArgs& Args);

	/** Dockable tab for properties */
	TSharedPtr< SDockableTab > PropertiesTab;

	/** Details view */
	TSharedPtr<class IDetailsView> DetailsView;

	UMenuEditorWidget* MenuEditUMGWidget = nullptr;

	/** The Custom Asset open within this editor */
	UMenu* Menu = nullptr;

	FString WidgetReferencePath = "WidgetBlueprint'/Psydekick/Visuals/2D/Menu/MenuEditWidget.MenuEditWidget'";
};
