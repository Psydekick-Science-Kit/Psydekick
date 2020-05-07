// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Framework/Text/TextLayout.h" 
#include "Math/Color.h"
#include "GameFramework/HUD.h"
#include "Engine/EngineTypes.h"

DECLARE_DELEGATE(FOnDurationTimerComplete);

class PSYDEKICK_API STextDisplay : public SBorder
{
public:
	SLATE_BEGIN_ARGS(STextDisplay)
	{}
	SLATE_END_ARGS()

	~STextDisplay();

	void Construct(const FArguments& InArgs);

	// @TODO: Convert these to slate attributes
	void SetText(const FString text);
	void SetColorAndOpacity(const FLinearColor Color);
	void SetBackgroundColor(const FLinearColor Color);

	void AddToViewport();
	void RemoveFromViewport();
	void ShowOnScreen(const float Duration);
	void SetAutoWrapText(const bool AutoWrap);
	void SetJustification(const ETextJustify::Type Justification);

protected:
	TSharedPtr<STextBlock> TextBlock;
	FSlateColorBrush BrushColor = FSlateColorBrush(FLinearColor(0, 0, 0, 0.5));
	FTimerHandle RemoveFromScreenTimerHandle;

	FOnDurationTimerComplete DurationTimerComplete;

};
