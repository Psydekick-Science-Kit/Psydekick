// Fill out your copyright notice in the Description page of Project Settings.

#include "Psydekick_Visuals_2D.h"
#include "PsydeKick.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Misc/OutputDeviceNull.h" 

#include "STextDisplay.h"
#include "SImageDisplay.h"
#include "SChoiceDisplay.h"

#include "Engine/Engine.h"


TSharedPtr<class SWidget> UPsydekick_Visuals_2D::CurrentWidget;


UPsydekick_Visuals_2D::UPsydekick_Visuals_2D(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
    UE_LOG(LogPsydeKick, Log, TEXT("Initialized Psydekick Visuals 2D Plugin"));
}

void UPsydekick_Visuals_2D::ShowText(UObject* WorldContextObject, FString text)
{
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
        UE_LOG(LogPsydeKick, Error, TEXT("Failed to create widget"));
    }
}

void UPsydekick_Visuals_2D::ClearScreen(UObject* WorldContextObject)
{
    GEngine->GameViewport->RemoveAllViewportWidgets();
}

void UPsydekick_Visuals_2D::ShowImage(UObject* WorldContextObject, UTexture2D* Image)
{
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
        UE_LOG(LogPsydeKick, Error, TEXT("Failed to create widget"));
    }
}


void UPsydekick_Visuals_2D::ShowChoices(const UObject* WorldContextObject, const FString prompt, const TArray<FString> choices, const FChoiceMade &ChoiceMade)
{
    SAssignNew(CurrentWidget, SChoiceDisplay);

    if (CurrentWidget.IsValid()) {
        TSharedPtr<SChoiceDisplay> myChoiceDisplay = StaticCastSharedPtr<SChoiceDisplay>(CurrentWidget);
        myChoiceDisplay->Init(prompt, choices, ChoiceMade);

        GEngine->GameViewport->AddViewportWidgetContent(
            SNew(SWeakWidget)
            .PossiblyNullContent(CurrentWidget.ToSharedRef())
        );
    }
    else {
        UE_LOG(LogPsydeKick, Error, TEXT("Failed to create widget"));
    }
}
