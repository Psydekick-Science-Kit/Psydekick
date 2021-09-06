// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StimulusConfiguration.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PSYDEKICK_API UStimulusConfiguration : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Psydekick|Stimuli")
	FString ToString();
};
