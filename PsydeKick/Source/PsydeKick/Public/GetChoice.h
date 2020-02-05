// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "Psydekick_Visuals_2D.h"

#include "GetChoice.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChoiceMadeOutputPin, FString, choice, uint8, index);

/**
 * 
 */
UCLASS()
class PSYDEKICK_API UGetChoice : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FChoiceMade ChoiceMade;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Psydekick|Visuals|2D")
	static UGetChoice* GetChoice(const UObject* WorldContextObject, const FString prompt, const TArray<FString> options);

	virtual void Activate() override;

private:
	const UObject* WorldContextObject;
	FString prompt;
	TArray<FString> options;
	/*
	UFUNCTION()
	void ExecuteAfterChoiceMade();
	*/
};
