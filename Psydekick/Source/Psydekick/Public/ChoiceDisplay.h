// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Slate.h"
#include "Psydekick_Visuals_2D.h"

class PSYDEKICK_API SChoiceDisplay : public SBorder
{
public:
	SLATE_BEGIN_ARGS(SChoiceDisplay)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void Init(FString prompt, TArray<FString> choices, const FChoiceMade &ChoiceMade);

private:
	FSlateColorBrush brushClr = FSlateColorBrush(FLinearColor(0, 0, 0, 0.5));

	TSharedPtr<STextBlock> TextBlock;

	TSharedRef<ITableRow> OnGenerateTile(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedPtr<STileView<TSharedPtr<FString>>> ChoiceContainer;
	TArray<TSharedPtr<FString>> Items;
	FChoiceMade OnChoiceMade;
	int32 count = 0;
};
