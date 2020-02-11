// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Slate.h"


#include "GameFramework/HUD.h" 

class PSYDEKICK_API STextDisplay : public SBorder
{
public:
	SLATE_BEGIN_ARGS(STextDisplay)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void SetText(FString text);

private:
	TSharedPtr<STextBlock> TextBlock;
	FSlateColorBrush brushClr = FSlateColorBrush(FLinearColor(0, 0, 0, 0.5));
};
