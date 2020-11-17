// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuTree/MenuTreeEditor.h"
#include "2D/MenuTree.h"
#include "PsydekickEd.h"

#include "Modules/ModuleManager.h"
#include "EditorStyleSet.h"
#include "Widgets/Docking/SDockTab.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Editor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StreamableManager.h"

#define LOCTEXT_NAMESPACE "MenuTreeEditor"

const FName FMenuTreeEditor::ToolkitFName(TEXT("MenuTreeEditor"));
const FName FMenuTreeEditor::PropertiesTabId(TEXT("MenuTreeEditor_Properties"));
const FName FMenuTreeEditor::MenuTreeEditTabId(TEXT("MenuTreeEditor_MenuEdit"));
const FName FMenuTreeEditor::MenuTreeEditorAppIdentifier(TEXT("MenuTreeEditorApp"));


void FMenuTreeEditor::InitMenuTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UMenuTree* InMenuTree)
{
	// Cache some values that will be used for our details view arguments
	const bool bIsUpdatable = false;
	const bool bAllowFavorites = true;
	const bool bIsLockable = false;

	// Set this Menu as our editing asset
	MenuTree = InMenuTree;

	// Retrieve the property editor module and assign properties to DetailsView
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(bIsUpdatable, bIsLockable, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Create the layout of our custom asset editor
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_MenuTreeEditor_Layout_v1")->AddArea
	(
		// Create a vertical area and spawn the toolbar
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->SetHideTabWell(true)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)->Split(
			// Split the tab and pass the tab id to the tab spawner
			FTabManager::NewSplitter()->Split
			(
				FTabManager::NewStack()
					->AddTab(MenuTreeEditTabId, ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
					->AddTab(PropertiesTabId, ETabState::OpenedTab)
			)
		)
	);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	// Initialize our custom asset editor
	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		MenuTreeEditorAppIdentifier,
		StandaloneDefaultLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		(UObject*)InMenuTree);

	// Set the asset we are editing in the details view
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject((UObject*)InMenuTree);
	}
}

void FMenuTreeEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_MenuTreeEditor", "Menu Tree Editor"));
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(MenuTreeEditTabId, FOnSpawnTab::CreateSP(this, &FMenuTreeEditor::SpawnMenuTreeEditTab))
		.SetDisplayName(LOCTEXT("MenuTreeEditTab", "Menu Tree Edit"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
		//.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FMenuTreeEditor::SpawnPropertiesTab))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

}

void FMenuTreeEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	// Unregister the tab manager from the asset editor toolkit
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	// Unregister our custom tab from the tab manager, making sure it is cleaned up when the editor gets destroyed
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
	InTabManager->UnregisterTabSpawner(MenuTreeEditTabId);
}

TSharedRef<SDockTab> FMenuTreeEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
{
	// Make sure we have the correct tab id
	check(Args.GetTabId() == PropertiesTabId);

	// Return a new slate dockable tab that contains our details view
	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
		.Label(LOCTEXT("GenericDetailsTitle", "Details"))
		.TabColorScale(GetTabColorScale())
		[
				// Provide the details view as this tab its content
				DetailsView.ToSharedRef()
		];
}

TSharedRef<SDockTab> FMenuTreeEditor::SpawnMenuTreeEditTab(const FSpawnTabArgs& Args)
{
	// Make sure we have the correct tab id
	check(Args.GetTabId() == MenuTreeEditTabId);
	UBlueprint* WidgetBlueprint = Cast<UBlueprint>(LoadAssetFromContent(WidgetReferencePath));

	if (WidgetBlueprint)
	{
		MenuTreeEditUMGWidget = CreateWidget<UMenuTreeEditorWidget>(GEditor->GetEditorWorldContext().World(), (UClass*)WidgetBlueprint->GeneratedClass);
		if(!MenuTree)
		{
			UE_LOG(LogPsydekickEd, Warning, TEXT("Oh no! Menu is null :("));
		}
		MenuTreeEditUMGWidget->SetMenuTree(MenuTree);

		return SNew(SDockTab)
			//.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
			.Label(LOCTEXT("MenuEditTitle", "Menu Tree Editor"))
			.TabColorScale(GetTabColorScale())
			[
					// Provide the details view as this tab its content
					MenuTreeEditUMGWidget->TakeWidget()
			];
	}
	else
	{
		UE_LOG(LogPsydekickEd, Warning, TEXT("Could not find MenuTreeEditWidget Blueprint at %s"), *WidgetReferencePath);
		return SNew(SDockTab)
			//.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
			.Label(LOCTEXT("MenuTreeEditTitle", "Menu Tree Editor"))
			.TabColorScale(GetTabColorScale());
	}
}

UObject* FMenuTreeEditor::LoadAssetFromContent(FString Path)
{
	FStringAssetReference* AssetRef = new FStringAssetReference(Path);
	FStreamableManager AssetLoader;
	UObject* LoadedAsset = nullptr;

	LoadedAsset = AssetLoader.LoadSynchronous(*AssetRef);
	delete AssetRef;

	return LoadedAsset;
}

FMenuTreeEditor::~FMenuTreeEditor()
{
	DetailsView.Reset();
	PropertiesTab.Reset();
}

FName FMenuTreeEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FMenuTreeEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Menu Tree Editor");
}

FText FMenuTreeEditor::GetToolkitToolTipText() const
{
	return LOCTEXT("ToolTip", "Menu Tree Editor");
}

FString FMenuTreeEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "AnimationDatabase ").ToString();
}

FLinearColor FMenuTreeEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Red;
}

#undef LOCTEXT_NAMESPACE
