// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "2D/ChoiceDisplay.h"

#include "Psydekick.h"

#include "SlateOptMacros.h"
#include "InputCoreTypes.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
#include "Engine/Engine.h"

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
			.HAlign(HAlign_Fill)
			.Padding(FMargin(16.0f))
			[
				SAssignNew(ChoiceContainer, STileView<TSharedPtr<FString>>)
				.ListItemsSource(&Items)
				.ItemAlignment(EListItemAlignment::CenterAligned)
				.OnGenerateTile(this, &SChoiceDisplay::OnGenerateTile)
			]
		];
}

TSharedRef<ITableRow> SChoiceDisplay::OnGenerateTile(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable) {
	int32 index = count++;
	FChoiceMade _onChoiceMade = OnChoiceMade;

	return SNew(STableRow<TSharedPtr<SWidget>>, OwnerTable)
		.Padding(FMargin(8.0f))
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.OnClicked_Lambda([Item, _onChoiceMade, index]()->FReply {
				_onChoiceMade.ExecuteIfBound(**Item, index);
				return FReply::Handled();
			})
			.Content()
			[
				SNew(STextBlock)
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 14))
				.Text(FText::FromString(*Item))
			]
		];
}

void SChoiceDisplay::Init(FString prompt, TArray<FString> choices, const FChoiceMade& ChoiceMade)
{
	OnChoiceMade = ChoiceMade;
	TextBlock->SetText(FText::FromString(prompt));

	Items.RemoveAll([](TSharedPtr<FString> Val) { return true; });
	count = 0;
	for (auto& Choice : choices) {
		TSharedPtr<FString> item = MakeShared<FString>(Choice);
		Items.Add(item);
	}
	ChoiceContainer->RequestListRefresh();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
