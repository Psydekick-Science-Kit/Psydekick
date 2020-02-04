// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Slate.h"

/**
 * 
 */
class SChoiceDisplay : public SBorder
{
public:
	SLATE_BEGIN_ARGS(SChoiceDisplay)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Init(FString prompt, TArray<FString> choices);

private:
	FSlateColorBrush brushClr = FSlateColorBrush(FLinearColor(0, 0, 0, 0.75));

	TSharedPtr<STextBlock> TextBlock;

	TSharedRef<ITableRow> OnGenerateTile(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedPtr<STileView<TSharedPtr<FString>>> ChoiceContainer;
	TArray<TSharedPtr<FString>> Items;
};
