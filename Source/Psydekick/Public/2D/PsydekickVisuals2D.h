// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Engine/Texture.h"

#include "2D/TextDisplay.h"
#include "2D/ImageDisplay.h"

#include "PsydekickVisuals2D.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FChoiceMade, FString, choice, int32, index);

UCLASS()
class PSYDEKICK_API APsydekickVisuals2D : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APsydekickVisuals2D();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// @TODO: determine how to properly type-check SWidgets at runtime so these can be a single collection
	TArray<TSharedPtr<STextDisplay>> TextWidgets;
	TArray<TSharedPtr<SImageDisplay>> ImageWidgets;
	TArray<TSharedPtr<class SChoiceDisplay>> ChoiceWidgets;

public:
	void ShowText(const FString Text, const float Duration, const FLinearColor TextColor, const FLinearColor BackgroundColor, const ETextJustify::Type Justification, const bool AutoWrapText);
	void ShowImage(UTexture* Image, FLinearColor BackgroundColor, EVerticalAlignment VAlign = EVerticalAlignment::VAlign_Center, EHorizontalAlignment HAlign = EHorizontalAlignment::HAlign_Center, int32 OffsetX = 0, int OffsetY = 0);
	void GetChoice(const FString Prompt, const TArray<FString> Options, const FChoiceMade& ChoiceMade);

	void ClearScreen(const bool PsydekickWidgetOnly = true);
	void ClearTexts();
	void ClearImages();

	void SetUIMode();
	void SetGameOnlyMode();
};
