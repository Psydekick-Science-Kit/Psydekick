// Fill out your copyright notice in the Description page of Project Settings.


#include "SChoiceDisplay.h"
#include "SlateOptMacros.h"
#include "PsydeKick.h"
#include "InputCoreTypes.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SChoiceDisplay::Construct(const FArguments& InArgs)
{
	SetBorderImage(&brushClr);

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Center)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(16.0f))
			[
				SAssignNew(TextBlock, STextBlock)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ColorAndOpacity(FLinearColor::White)
				.ShadowOffset(FIntPoint(-1, 1))
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 24))
				.Visibility(EVisibility::Visible)
			]

			+SVerticalBox::Slot()
			.VAlign(VAlign_Fill)
			.Padding(FMargin(16.0f))
			[
				SAssignNew(ChoiceContainer, STileView<TSharedPtr<FString>>)
				.ListItemsSource(&Items)
				.OnGenerateTile(this, &SChoiceDisplay::OnGenerateTile)
				
			]
		];
}


TSharedRef<ITableRow> SChoiceDisplay::OnGenerateTile(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable) {
	// @TODO: bind callback to button click
	return SNew(STableRow<TSharedPtr<SWidget>>, OwnerTable)
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.Content()
			[
				SNew(STextBlock)
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 14))
				.Text(FText::FromString(*Item))
			]
		];
}


void SChoiceDisplay::Init(FString prompt, TArray<FString> choices)
{
	TextBlock->SetText(FText::FromString(prompt));

	Items.RemoveAll([](TSharedPtr<FString> Val) { return true; });
	for (auto& Choice : choices) {
		TSharedPtr<FString> item = MakeShared<FString>(Choice);
		Items.Add(item);
	}
	ChoiceContainer->RequestListRefresh();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
