// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuEditorWidget.generated.h"

class UMenu;
/**
 *
 */
UCLASS()
class PSYDEKICKED_API UMenuEditorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetMenu(UMenu* Menu);

};
