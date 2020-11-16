// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Menu.h"
#include "MenuEditor.h"


DECLARE_LOG_CATEGORY_EXTERN(LogPsydekickEd, Log, All);

class FPsydekickEdModule : public IModuleInterface//, public IHasMenuExtensibility, public IHasToolBarExtensibility
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual TSharedRef<FMenuEditor> CreateMenuEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMenu* Menu);

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
