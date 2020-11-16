#include "AssetTypeActions_Menu.h"
#include "Menu.h"
#include "PsydekickEd.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_Menu"

FText FAssetTypeActions_Menu::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_Menu", "AssetTypeActions_Menu", "Menu");
}

FColor FAssetTypeActions_Menu::GetTypeColor() const
{
	return FColor::Magenta;
}

UClass* FAssetTypeActions_Menu::GetSupportedClass() const
{
	return UMenu::StaticClass();
}

void FAssetTypeActions_Menu::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Menu = Cast<UMenu>(*ObjIt);
		if (Menu != NULL)
		{
			FPsydekickEdModule* PsydekickEdModule = &FModuleManager::LoadModuleChecked<FPsydekickEdModule>("PsydekickEd");
			PsydekickEdModule->CreateMenuEditor(Mode, EditWithinLevelEditor, Menu);
		}
	}
}

uint32 FAssetTypeActions_Menu::GetCategories()
{
	return EAssetTypeCategories::UI;
}

#undef LOCTEXT_NAMESPACE
