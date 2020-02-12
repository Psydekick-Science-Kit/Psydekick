// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileMediaSource.h" 

#include "Psydekick_Visuals_2D.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FChoiceMade, FString, choice, uint8, index);

UCLASS()
class PSYDEKICK_API UPsydekick_Visuals_2D : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ShowText(const UObject* WorldContextObject, FString text);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ClearScreen(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ShowImage(const UObject* WorldContextObject, UTexture* Image);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options, const FChoiceMade &ChoiceMade);

	static TSharedPtr<class SWidget> CurrentWidget;
};
