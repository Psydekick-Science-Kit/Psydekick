// Fill out your copyright notice in the Description page of Project Settings.

#include "GetChoice.h"
#include "Psydekick_Visuals_2D.h"

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

void UGetChoice::OnChoiceMade(FString Choice, uint8 Index)
{
	ChoiceMade.Broadcast(Choice, Index);
}

void UGetChoice::Activate()
{
	UPsydekick_Visuals_2D::GetChoice(WorldContextObject, Prompt, Options, ChoiceMadeDelegate);
}
