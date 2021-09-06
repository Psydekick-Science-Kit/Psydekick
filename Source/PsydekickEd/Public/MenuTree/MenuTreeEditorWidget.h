// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuTreeEditorWidget.generated.h"

class UMenuTree;

UCLASS()
class PSYDEKICKED_API UMenuTreeEditorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void LoadMenuTree(UMenuTree* Menu);

};
