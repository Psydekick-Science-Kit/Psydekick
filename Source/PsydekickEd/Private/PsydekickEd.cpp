// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PsydekickEd.h"

#include "AssetToolsModule.h"
#include "MenuTree/AssetTypeActions_MenuTree.h"
#include "MenuTree/MenuTreeEditor.h"

#define LOCTEXT_NAMESPACE "FPsydekickEdModule"

DEFINE_LOG_CATEGORY(LogPsydekickEd)

void FPsydekickEdModule::StartupModule()
{
	UE_LOG(LogPsydekickEd, Log, TEXT("PsydekickEd compiled %s at %s"), TEXT(__DATE__), TEXT(__TIME__));

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_MenuTree()));
}

void FPsydekickEdModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		// Unregister our custom created assets from the AssetTools
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 i = 0; i < CreatedAssetTypeActions.Num(); ++i)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[i].ToSharedRef());
		}
	}

	CreatedAssetTypeActions.Empty();
}

TSharedRef<FMenuTreeEditor> FPsydekickEdModule::CreateMenuTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMenuTree* MenuTree)
{
	// Initialize and spawn a new custom asset editor with the provided parameters
	TSharedRef<FMenuTreeEditor> MenuTreeEditor(new FMenuTreeEditor());
	MenuTreeEditor->InitMenuTreeEditor(Mode, InitToolkitHost, MenuTree);

	return MenuTreeEditor;
}

void FPsydekickEdModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FPsydekickEdModule, PsydekickEd)
