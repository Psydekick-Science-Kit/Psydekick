// Fill out your copyright notice in the Description page of Project Settings.

#include "TextDisplay.h"
#include "SlateOptMacros.h"

#include "Misc/Paths.h"
#include "Layout/Visibility.h"

#include "Engine/Engine.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STextDisplay::Construct(const FArguments& InArgs)
{
	SetBorderImage(&BrushColor);
	SetPadding(FMargin(50.0f, 50.0f));

	ChildSlot
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		[
			SAssignNew(TextBlock, STextBlock)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ColorAndOpacity(FLinearColor::White)
				.ShadowOffset(FIntPoint(-1, 1))
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 24))
				.Visibility(EVisibility::Visible)
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

STextDisplay::~STextDisplay()
{
	if(GEngine && GEngine->GameViewport && GEngine->GameViewport->GetWorld())
	{
		FTimerManager& TimerManager = GEngine->GameViewport->GetWorld()->GetTimerManager();

		if(RemoveFromScreenTimerHandle.IsValid() && TimerManager.IsTimerActive(RemoveFromScreenTimerHandle))
		{
			TimerManager.ClearTimer(RemoveFromScreenTimerHandle);
		}
	}
}

void STextDisplay::SetAutoWrapText(const bool AutoWrap) {
	TextBlock->SetAutoWrapText(AutoWrap);
}

void STextDisplay::SetJustification(const ETextJustify::Type Justification) {
	TextBlock->SetJustification(Justification);
}

void STextDisplay::SetText(const FString Text)
{
	TextBlock->SetText(FText::FromString(Text.ReplaceEscapedCharWithChar()));
}

void STextDisplay::SetColorAndOpacity(const FLinearColor Color)
{
	TextBlock->SetColorAndOpacity(FSlateColor(Color));
}

void STextDisplay::SetBackgroundColor(const FLinearColor Color)
{
	BrushColor = FSlateColorBrush(Color);
	SetBorderImage(&BrushColor);
}

void STextDisplay::ShowOnScreen(const float Duration)
{
	AddToViewport();
	if(Duration > 0.0f)
	{
		DurationTimerComplete.BindRaw(this, &STextDisplay::RemoveFromViewport);

		GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(
			RemoveFromScreenTimerHandle,
			DurationTimerComplete,
			Duration,
			false,
			Duration
		);  
	}
}

void STextDisplay::AddToViewport()
{
	GEngine->GameViewport->AddViewportWidgetContent(AsShared());
}

void STextDisplay::RemoveFromViewport()
{
	RemoveFromScreenTimerHandle.Invalidate();
	GEngine->GameViewport->RemoveViewportWidgetContent(AsShared());
}

