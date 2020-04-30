// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StimulusConfiguration.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PSYDEKICK_API UStimulusConfiguration : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString ToString();
};
