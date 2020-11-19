// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "2D/MenuTree.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuTreeWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeafSelected, UMenuTreeEntryWrapper*, MenuTreeEntry);

/**
 *
 */
UCLASS()
class PSYDEKICK_API UMenuTreeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Psydekick|Menu")
	void LoadMenuTree(UMenuTree* MenuTree);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FLeafSelected LeafSelected;

};
