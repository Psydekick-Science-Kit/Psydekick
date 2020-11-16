// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuFactory.h"
#include "Menu.h"

UMenuFactory::UMenuFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMenu::StaticClass();
}

UObject* UMenuFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UMenu* Menu = NewObject<UMenu>(InParent, Class, Name, Flags);

	return Menu;
}
