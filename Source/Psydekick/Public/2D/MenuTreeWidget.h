// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "2D/MenuTree.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"

#include "MenuTreeWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLeafSelected, UMenuTreeEntryWrapper*, MenuTreeEntry);

UCLASS()
class PSYDEKICK_API UMenuTreeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Psydekick|Menu")
	void LoadMenuTree(UMenuTree* MenuTree);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FLeafSelected LeafSelected;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWidgetAnimation* InAnimation = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWidgetAnimation* OutAnimation = nullptr;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Show();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Hide();
};
