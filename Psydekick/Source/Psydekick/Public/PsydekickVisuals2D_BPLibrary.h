// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "PsydekickVisuals2D.h"

#include "PsydekickVisuals2D_BPLibrary.generated.h"

UCLASS()
class PSYDEKICK_API UPsydekickVisuals2D_BPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	static APsydekickVisuals2D* PKVisuals2DActor;

public:
	static APsydekickVisuals2D* GetPKVisuals2DActor(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject, AdvancedDisplay = 2))
	static void ShowText(const UObject* WorldContextObject, const FString Text, const float Duration = 0.0f, FLinearColor TextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.75f));

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ClearScreen(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void ShowImage(const UObject* WorldContextObject, UTexture* Image);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options, const FChoiceMade& ChoiceMade);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void SetUIMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Visuals|2D", meta = (WorldContext = WorldContextObject))
	static void SetGameOnlyMode(const UObject* WorldContextObject);
};
