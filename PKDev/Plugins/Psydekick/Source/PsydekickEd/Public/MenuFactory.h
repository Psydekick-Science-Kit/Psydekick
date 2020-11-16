// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MenuFactory.generated.h"

/**
 *
 */
UCLASS()
class PSYDEKICKED_API UMenuFactory : public UFactory
{
	GENERATED_BODY()

	UMenuFactory();

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
