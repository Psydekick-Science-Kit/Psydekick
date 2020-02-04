// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "STextDisplay.h"

#include "Psydekick_Visuals_2D.generated.h"

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

	// @TODO: modify for callback on selection
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Psydekick show choices"), Category = "Psydekick", meta = (WorldContext = WorldContextObject))
	static void ShowChoices(UObject* WorldContextObject, FString prompt, TArray<FString> choices);

	static TSharedPtr<class SWidget> CurrentWidget;
};
