// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "STextDisplay.h"

#include "Psydekick_Visuals_2D.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChoiceMade, FString, choice, uint8, index);
//DECLARE_DYNAMIC_DELEGATE_TwoParams(FChoiceMade_, FString, choice, uint8, index);


/**
 * 
 */
UCLASS()
class PSYDEKICK_API UPsydekick_Visuals_2D : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Psydekick show text"), Category = "Psydekick", meta = (WorldContext = WorldContextObject))
	static void ShowText(UObject* WorldContextObject, FString text);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Psydekick clear screen"), Category = "Psydekick", meta = (WorldContext = WorldContextObject))
	static void ClearScreen(UObject* WorldContextObject);

	//UFUNCTION(BlueprintCallable, meta = (Keywords = "Psydekick show choices"), Category = "Psydekick", meta = (WorldContext = WorldContextObject))
	static void ShowChoices(const UObject* WorldContextObject, const FString prompt, const TArray<FString> choices, const FChoiceMade &ChoiceMade);

	static TSharedPtr<class SWidget> CurrentWidget;
};