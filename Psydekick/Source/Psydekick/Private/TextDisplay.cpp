// Fill out your copyright notice in the Description page of Project Settings.

#include "TextDisplay.h"
#include "SlateOptMacros.h"

#include "Misc/Paths.h"
#include "Layout/Visibility.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STextDisplay::Construct(const FArguments& InArgs)
{
	SetBorderImage(&brushClr);

	ChildSlot
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SAssignNew(TextBlock, STextBlock)
			.ShadowColorAndOpacity(FLinearColor::Black)
			.ColorAndOpacity(FLinearColor::White)
			.ShadowOffset(FIntPoint(-1, 1))
			.AutoWrapText(true)
			.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 24))
			.Visibility(EVisibility::Visible)
		];
}

void STextDisplay::SetText(FString text) {
	TextBlock->SetText(FText::FromString(text));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
