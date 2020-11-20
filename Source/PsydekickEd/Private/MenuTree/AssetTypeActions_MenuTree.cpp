#include "MenuTree/AssetTypeActions_MenuTree.h"
#include "2D/MenuTree.h"
#include "PsydekickEd.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_MenuTree"

FText FAssetTypeActions_MenuTree::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_MenuTree", "AssetTypeActions_MenuTree", "Menu Tree");
}

FColor FAssetTypeActions_MenuTree::GetTypeColor() const
{
	return FColor::Magenta;
}

UClass* FAssetTypeActions_MenuTree::GetSupportedClass() const
{
	return UMenuTree::StaticClass();
}

void FAssetTypeActions_MenuTree::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto MenuTree = Cast<UMenuTree>(*ObjIt);
		if (MenuTree != NULL)
		{
			FPsydekickEdModule* PsydekickEdModule = &FModuleManager::LoadModuleChecked<FPsydekickEdModule>("PsydekickEd");
			PsydekickEdModule->CreateMenuTreeEditor(Mode, EditWithinLevelEditor, MenuTree);
		}
	}
}

uint32 FAssetTypeActions_MenuTree::GetCategories()
{
	return EAssetTypeCategories::UI;
}

#undef LOCTEXT_NAMESPACE
