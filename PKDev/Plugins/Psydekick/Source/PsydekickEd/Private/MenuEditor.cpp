// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuEditor.h"

#include "Menu.h"

#include "Modules/ModuleManager.h"
#include "EditorStyleSet.h"
#include "Widgets/Docking/SDockTab.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Editor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StreamableManager.h"

#define LOCTEXT_NAMESPACE "MenuEditor"

const FName FMenuEditor::ToolkitFName(TEXT("MenuEditor"));
const FName FMenuEditor::PropertiesTabId(TEXT("MenuEditor_Properties"));
const FName FMenuEditor::MenuEditTabId(TEXT("MenuEditor_MenuEdit"));
const FName FMenuEditor::MenuEditorAppIdentifier(TEXT("MenuEditorApp"));


void FMenuEditor::InitMenuEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UMenu* InMenu)
{
	// Cache some values that will be used for our details view arguments
	const bool bIsUpdatable = false;
	const bool bAllowFavorites = true;
	const bool bIsLockable = false;

	// Set this Menu as our editing asset
	Menu = InMenu;

	// Retrieve the property editor module and assign properties to DetailsView
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(bIsUpdatable, bIsLockable, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Create the layout of our custom asset editor
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_MenuEditor_Layout_v1")->AddArea
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
					->AddTab(MenuEditTabId, ETabState::OpenedTab)
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
		MenuEditorAppIdentifier,
		StandaloneDefaultLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		(UObject*)InMenu);

	// Set the asset we are editing in the details view
	if (DetailsView.IsValid())
	{
		DetailsView->SetObject((UObject*)InMenu);
	}
}

void FMenuEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_MenuEditor", "Menu Editor"));
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(MenuEditTabId, FOnSpawnTab::CreateSP(this, &FMenuEditor::SpawnMenuEditTab))
		.SetDisplayName(LOCTEXT("MenuEditTab", "Menu Edit"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef());
		//.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FMenuEditor::SpawnPropertiesTab))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategory.ToSharedRef())
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

}

void FMenuEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	// Unregister the tab manager from the asset editor toolkit
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	// Unregister our custom tab from the tab manager, making sure it is cleaned up when the editor gets destroyed
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
	InTabManager->UnregisterTabSpawner(MenuEditTabId);
}

TSharedRef<SDockTab> FMenuEditor::SpawnPropertiesTab(const FSpawnTabArgs& Args)
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

TSharedRef<SDockTab> FMenuEditor::SpawnMenuEditTab(const FSpawnTabArgs& Args)
{
	// Make sure we have the correct tab id
	check(Args.GetTabId() == MenuEditTabId);
	UBlueprint* WidgetBlueprint = Cast<UBlueprint>(LoadAssetFromContent(WidgetReferencePath));

	if (WidgetBlueprint)
	{
		MenuEditUMGWidget = CreateWidget<UMenuEditorWidget>(GEditor->GetEditorWorldContext().World(), (UClass*)WidgetBlueprint->GeneratedClass);
		if(!Menu)
		{
			UE_LOG(LogPsydekickEd, Warning, TEXT("Oh no! Menu is null :("));
		}
		MenuEditUMGWidget->SetMenu(Menu);

		return SNew(SDockTab)
			//.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
			.Label(LOCTEXT("MenuEditTitle", "Menu Editor"))
			.TabColorScale(GetTabColorScale())
			[
					// Provide the details view as this tab its content
					MenuEditUMGWidget->TakeWidget()
			];
	}
	else
	{
		UE_LOG(LogPsydekickEd, Warning, TEXT("Could not find MenuEditWidget Blueprint"));
		return SNew(SDockTab)
			//.Icon(FEditorStyle::GetBrush("GenericEditor.Tabs.Properties"))
			.Label(LOCTEXT("MenuEditTitle", "Menu Editor"))
			.TabColorScale(GetTabColorScale());
	}
}

UObject* FMenuEditor::LoadAssetFromContent(FString Path)
{
	FStringAssetReference* AssetRef = new FStringAssetReference(Path);
	FStreamableManager AssetLoader;
	UObject* LoadedAsset = nullptr;

	LoadedAsset = AssetLoader.LoadSynchronous(*AssetRef);
	delete AssetRef;

	return LoadedAsset;
}

FMenuEditor::~FMenuEditor()
{
	DetailsView.Reset();
	PropertiesTab.Reset();
}

FName FMenuEditor::GetToolkitFName() const
{
	return ToolkitFName;
}

FText FMenuEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Menu Editor");
}

FText FMenuEditor::GetToolkitToolTipText() const
{
	return LOCTEXT("ToolTip", "Menu Editor");
}

FString FMenuEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "AnimationDatabase ").ToString();
}

FLinearColor FMenuEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Red;
}

#undef LOCTEXT_NAMESPACE
