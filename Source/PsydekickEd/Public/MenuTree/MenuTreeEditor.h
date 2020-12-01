#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MenuTree/MenuTreeEditorWidget.h"

class IDetailsView;
class SDockableTab;
class UMenuTree;

class PSYDEKICKED_API FMenuTreeEditor : public FAssetEditorToolkit
{
public:
	void InitMenuTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UMenuTree* InMenuTree);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	/** Destructor */
	virtual ~FMenuTreeEditor();

	#pragma region IToolkit interface

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual bool IsPrimaryEditor() const override { return true; }

	#pragma endregion

	static const FName ToolkitFName;
	static const FName PropertiesTabId;
	static const FName MenuTreeEditTabId;
	static const FName MenuTreeEditorAppIdentifier;

private:

	// Create the properties tab and its content
	TSharedRef<SDockTab> SpawnPropertiesTab(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnMenuTreeEditTab(const FSpawnTabArgs& Args);

	TSharedPtr< SDockableTab > PropertiesTab;
	TSharedPtr<class IDetailsView> DetailsView;

	UMenuTreeEditorWidget* MenuTreeEditUMGWidget = nullptr;

	UMenuTree* MenuTree = nullptr;

	FString WidgetReferencePath = "WidgetBlueprint'/Psydekick/Visuals/2D/Menu/Editor/MenuTreeEditWidget.MenuTreeEditWidget'";
};
