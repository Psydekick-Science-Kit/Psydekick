// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "MenuTree/MenuTreeFactory.h"
#include "2D/MenuTree.h"

UMenuTreeFactory::UMenuTreeFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMenuTree::StaticClass();
}

UObject* UMenuTreeFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UMenuTree* MenuTree = NewObject<UMenuTree>(InParent, Class, Name, Flags);

	return MenuTree;
}
