// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "IAssetTools.h"
#include "IAssetTypeActions.h"

#include "MenuTree/MenuTreeEditor.h"
#include "2D/MenuTree.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPsydekickEd, Log, All);

class FPsydekickEdModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual TSharedRef<FMenuTreeEditor> CreateMenuTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UMenuTree* MenuTree);

	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
