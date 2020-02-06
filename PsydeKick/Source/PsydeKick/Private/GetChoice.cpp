// Fill out your copyright notice in the Description page of Project Settings.


#include "GetChoice.h"
#include "Psydekick_Visuals_2D.h"

UGetChoice::UGetChoice(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer), WorldContextObject(nullptr), prompt(TEXT("Please make a choice")), options(TArray<FString>()) 
{
}

UGetChoice* UGetChoice::GetChoice(const UObject* WorldContextObject, const FString prompt, const TArray<FString> options)
{
	UGetChoice* bpNode = NewObject<UGetChoice>();
	bpNode->WorldContextObject = WorldContextObject;
	bpNode->prompt = prompt;
	bpNode->options = options;
	
	return bpNode;
}

void UGetChoice::Activate()
{
	UPsydekick_Visuals_2D::ShowChoices(WorldContextObject, prompt, options, ChoiceMade);
}
