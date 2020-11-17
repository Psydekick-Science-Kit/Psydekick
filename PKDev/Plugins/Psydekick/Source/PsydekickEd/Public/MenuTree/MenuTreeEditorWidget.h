// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuTreeEditorWidget.generated.h"

class UMenuTree;
/**
 *
 */
UCLASS()
class PSYDEKICKED_API UMenuTreeEditorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetMenuTree(UMenuTree* Menu);

};
