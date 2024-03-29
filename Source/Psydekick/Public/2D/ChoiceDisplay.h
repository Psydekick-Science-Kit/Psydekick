// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STileView.h"
#include "Brushes/SlateColorBrush.h"

#include "PsydekickVisuals2D.h"

class PSYDEKICK_API SChoiceDisplay : public SBorder
{
public:
	SLATE_BEGIN_ARGS(SChoiceDisplay)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	void Init(FString prompt, TArray<FString> choices, const class FChoiceMade &ChoiceMade);

private:
	FSlateColorBrush brushClr = FSlateColorBrush(FLinearColor(0, 0, 0, 0.5));

	TSharedPtr<STextBlock> TextBlock;
	TSharedRef<ITableRow> OnGenerateTile(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedPtr<STileView<TSharedPtr<FString>>> ChoiceContainer;
	TArray<TSharedPtr<FString>> Items;
	class FChoiceMade OnChoiceMade;
	int32 count = 0;
};
