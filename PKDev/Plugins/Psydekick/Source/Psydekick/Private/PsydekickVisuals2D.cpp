// Fill out your copyright notice in the Description page of Project Settings.


#include "PsydekickVisuals2D.h"
#include "Psydekick.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceNull.h"

#include "TextDisplay.h"
#include "ImageDisplay.h"
#include "ChoiceDisplay.h"
#include "Widgets/SWeakWidget.h"

#include "Engine/Engine.h"

// Sets default values
APsydekickVisuals2D::APsydekickVisuals2D()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APsydekickVisuals2D::BeginPlay()
{
	Super::BeginPlay();
}

void APsydekickVisuals2D::ShowText(const FString Text, const float Duration, const FLinearColor TextColor, const FLinearColor BackgroundColor, const ETextJustify::Type Justification, const bool AutoWrapText)
{
	TSharedPtr<class STextDisplay> TextDisplay = SNew(STextDisplay);

	if (TextDisplay.IsValid())
	{
		TextDisplay->SetText(Text);
		TextDisplay->SetColorAndOpacity(TextColor);
		TextDisplay->SetBackgroundColor(BackgroundColor);
		TextDisplay->SetJustification(Justification);
		TextDisplay->SetAutoWrapText(AutoWrapText);
		TextDisplay->ShowOnScreen(Duration);

		TextWidgets.Emplace(TextDisplay);
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("Failed to create widget"));
	}
}

void APsydekickVisuals2D::ShowImage(UTexture* Image, FLinearColor BackgroundColor, EVerticalAlignment VAlign, EHorizontalAlignment HAlign, int32 OffsetX, int OffsetY)
{
	TSharedPtr<class SImageDisplay> ImageDisplay = SNew(SImageDisplay);

	if (ImageDisplay.IsValid())
	{
		ImageDisplay->SetImage(Image);
		ImageDisplay->SetVAlign(VAlign);
		ImageDisplay->SetHAlign(HAlign);
		ImageDisplay->SetBackgroundColor(BackgroundColor);
		ImageDisplay->SetOffsets(OffsetX, OffsetY);

		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(ImageDisplay)
		);

		ImageWidgets.Emplace(ImageDisplay);
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("Failed to create widget"));
	}
}

void APsydekickVisuals2D::ClearScreen(const bool PsydekickWidgetOnly)
{
	if(PsydekickWidgetOnly)
	{
		for(auto& Widget : TextWidgets)
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(Widget.ToSharedRef());
		}
		for(auto& Widget : ImageWidgets)
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(Widget.ToSharedRef());
		}
		for(auto& Widget : ChoiceWidgets)
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(Widget.ToSharedRef());
		}
	}
	else {
		GEngine->GameViewport->RemoveAllViewportWidgets();
	}
	TextWidgets.Empty();
	ImageWidgets.Empty();
	ChoiceWidgets.Empty();
}

void APsydekickVisuals2D::ClearTexts()
{
	for(int32 i=TextWidgets.Num()-1; i>=0; i--)
	{
		TSharedPtr<STextDisplay> WidgetPtr = TextWidgets[i];
		GEngine->GameViewport->RemoveViewportWidgetContent(WidgetPtr.ToSharedRef());
		TextWidgets.RemoveAt(i);
	}
}

void APsydekickVisuals2D::ClearImages()
{
	for(int32 i=ImageWidgets.Num()-1; i>=0; i--)
	{
		TSharedPtr<SImageDisplay> WidgetPtr = ImageWidgets[i];
		GEngine->GameViewport->RemoveViewportWidgetContent(WidgetPtr.ToSharedRef());
		ImageWidgets.RemoveAt(i);
	}
}


void APsydekickVisuals2D::GetChoice(const FString Prompt, const TArray<FString> Options, const FChoiceMade &ChoiceMade)
{
	ClearScreen();
	SetUIMode();

	TSharedPtr<class SChoiceDisplay> ChoiceDisplay = SNew(SChoiceDisplay);

	if (ChoiceDisplay.IsValid())
	{
		ChoiceDisplay->Init(Prompt, Options, ChoiceMade);

		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(ChoiceDisplay)
		);

		ChoiceWidgets.Emplace(ChoiceDisplay.Get());
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("Failed to create widget"));
	}
}

void APsydekickVisuals2D::SetUIMode()
{
	UWorld* World = GetWorld();
	APlayerController* controller = UGameplayStatics::GetPlayerController(World, 0);

	if(controller != nullptr)
	{
		FInputModeGameAndUI GameAndUIMode;
		controller->SetInputMode(GameAndUIMode);
		controller->bShowMouseCursor = true;

		UE_LOG(LogPsydekick, Log, TEXT("UI mode activated"));
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("Failed setting game mode: Invalid world context object"));
	}
}

void APsydekickVisuals2D::SetGameOnlyMode()
{
	UWorld* World = GetWorld();
	APlayerController* controller = UGameplayStatics::GetPlayerController(World, 0);

	if(controller != nullptr)
	{
		FInputModeGameOnly GameOnlyMode;
		controller->SetInputMode(GameOnlyMode);
		controller->bShowMouseCursor = false;

		UE_LOG(LogPsydekick, Log, TEXT("Game only mode activated"));
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("Failed setting game mode: Invalid world context object"));
	}
}
