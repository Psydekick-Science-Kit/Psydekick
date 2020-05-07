// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Engine/Texture.h"

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

	TSharedPtr<class SWidget> CurrentWidget;

public:	
	void ShowText(const FString Text, const float Duration, const FLinearColor TextColor, const FLinearColor BackgroundColor, const ETextJustify::Type Justification, const bool AutoWrapText);
	void ClearScreen();
	void ShowImage(UTexture* Image);
	void GetChoice(const FString Prompt, const TArray<FString> Options, const FChoiceMade& ChoiceMade);
	void SetUIMode();
	void SetGameOnlyMode();	
};
