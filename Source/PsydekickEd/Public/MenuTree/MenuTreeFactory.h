// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MenuTreeFactory.generated.h"

UCLASS()
class PSYDEKICKED_API UMenuTreeFactory : public UFactory
{
	GENERATED_BODY()

	UMenuTreeFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
