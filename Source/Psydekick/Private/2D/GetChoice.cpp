// Fill out your copyright notice in the Description page of Project Settings.

#include "2D/GetChoice.h"

#include "2D/PsydekickVisuals2D_BPLibrary.h"

UGetChoice::UGetChoice(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer), WorldContextObject(nullptr), Prompt(TEXT("Please make a choice")), Options(TArray<FString>())
{
	ChoiceMadeDelegate.BindUFunction(this, "OnChoiceMade");
}

UGetChoice* UGetChoice::GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options)
{
	UGetChoice* bpNode = NewObject<UGetChoice>();
	bpNode->WorldContextObject = WorldContextObject;
	bpNode->Prompt = Prompt;
	bpNode->Options = Options;

	return bpNode;
}

void UGetChoice::Activate()
{
	UPsydekickVisuals2D_BPLibrary::SetUIMode(WorldContextObject);
	UPsydekickVisuals2D_BPLibrary::GetChoice(WorldContextObject, Prompt, Options, ChoiceMadeDelegate);
}

void UGetChoice::OnChoiceMade(FString Choice, uint8 Index)
{
	UPsydekickVisuals2D_BPLibrary::SetGameOnlyMode(WorldContextObject);
	ChoiceMade.Broadcast(Choice, Index);
}

