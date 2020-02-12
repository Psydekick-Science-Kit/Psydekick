// Fill out your copyright notice in the Description page of Project Settings.

#include "Psydekick_Visuals_2D.h"
#include "Psydekick.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Misc/OutputDeviceNull.h" 

#include "TextDisplay.h"
#include "ImageDisplay.h"
#include "ChoiceDisplay.h"

#include "Engine/Engine.h"


TSharedPtr<class SWidget> UPsydekick_Visuals_2D::CurrentWidget;

UPsydekick_Visuals_2D::UPsydekick_Visuals_2D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPsydekick_Visuals_2D::ShowText(const UObject* WorldContextObject, const FString text)
{
    UPsydekick_Visuals_2D::ClearScreen(WorldContextObject);
    SAssignNew(CurrentWidget, STextDisplay);

    if (CurrentWidget.IsValid()) {
        TSharedPtr<STextDisplay> myTextDisplay = StaticCastSharedPtr<STextDisplay>(CurrentWidget);
        myTextDisplay->SetText(text);

        GEngine->GameViewport->AddViewportWidgetContent(
            SNew(SWeakWidget)
            .PossiblyNullContent(CurrentWidget.ToSharedRef())
        );
    }
    else {
        UE_LOG(LogPsydekick, Error, TEXT("Failed to create widget"));
    }
}

void UPsydekick_Visuals_2D::ClearScreen(const UObject* WorldContextObject)
{
    GEngine->GameViewport->RemoveAllViewportWidgets();
}

void UPsydekick_Visuals_2D::ShowImage(const UObject* WorldContextObject, UTexture* Image)
{
    UPsydekick_Visuals_2D::ClearScreen(WorldContextObject);
    SAssignNew(CurrentWidget, SImageDisplay);

    if (CurrentWidget.IsValid()) {
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

void UPsydekick_Visuals_2D::GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options, const FChoiceMade &ChoiceMade)
{
    UPsydekick_Visuals_2D::ClearScreen(WorldContextObject);
    SAssignNew(CurrentWidget, SChoiceDisplay);

    if (CurrentWidget.IsValid()) {
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
