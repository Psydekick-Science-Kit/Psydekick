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
	ClearScreen();
	SAssignNew(CurrentWidget, STextDisplay);

	if (CurrentWidget.IsValid())
	{
		TSharedPtr<STextDisplay> MyTextDisplay = StaticCastSharedPtr<STextDisplay>(CurrentWidget);
		MyTextDisplay->SetText(Text);
		MyTextDisplay->SetColorAndOpacity(TextColor);
		MyTextDisplay->SetBackgroundColor(BackgroundColor);
		MyTextDisplay->SetJustification(Justification);
		MyTextDisplay->SetAutoWrapText(AutoWrapText);
		MyTextDisplay->ShowOnScreen(Duration);
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("Failed to create widget"));
	}
}

void APsydekickVisuals2D::ClearScreen(const bool PsydekickWidgetOnly)
{
	if(PsydekickWidgetOnly)
	{
		if(CurrentWidget.IsValid())
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(CurrentWidget.ToSharedRef());
		}
	}
	else {
		GEngine->GameViewport->RemoveAllViewportWidgets();
	}
	
}

void APsydekickVisuals2D::ShowImage(UTexture* Image)
{
	ClearScreen();
	SAssignNew(CurrentWidget, SImageDisplay);

	if (CurrentWidget.IsValid())
	{
		TSharedPtr<SImageDisplay> MyImageDisplay = StaticCastSharedPtr<SImageDisplay>(CurrentWidget);
		MyImageDisplay->SetImage(Image);

		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(CurrentWidget.ToSharedRef())
		);
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("Failed to create widget"));
	}
}

void APsydekickVisuals2D::GetChoice(const FString Prompt, const TArray<FString> Options, const FChoiceMade &ChoiceMade)
{
	ClearScreen();
	SetUIMode();

	SAssignNew(CurrentWidget, SChoiceDisplay);

	if (CurrentWidget.IsValid())
	{
		TSharedPtr<SChoiceDisplay> myChoiceDisplay = StaticCastSharedPtr<SChoiceDisplay>(CurrentWidget);
		myChoiceDisplay->Init(Prompt, Options, ChoiceMade);

		GEngine->GameViewport->AddViewportWidgetContent(
			SNew(SWeakWidget)
			.PossiblyNullContent(CurrentWidget.ToSharedRef())
		);
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
