// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/DateTime.h"
#include "Misc/Timespan.h"

#include "Stopwatch.generated.h"

UENUM(BlueprintType)
enum class EStopwatchState : uint8
{
	STOPPED  UMETA(DisplayName="Stopped"),
	RUNNING  UMETA(DisplayName="Running"),
	PAUSED   UMETA(DisplayName="Paused")
};

/**
 * 
 */
UCLASS(BlueprintType)
class PSYDEKICK_API UStopwatch : public UObject
{
	GENERATED_BODY()

protected:
	FTimespan AccumulatedTime;
	FTimespan GetCurrentTimeSince(FDateTime When);

public:
	UPROPERTY(BlueprintReadOnly)
	EStopwatchState State;

	UPROPERTY(BlueprintReadWrite)
	TArray<FTimespan> Laps;

	UPROPERTY(BlueprintReadOnly)
	FDateTime LapStartTime = FDateTime::MinValue();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void Start();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	FTimespan NewLap();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	FTimespan PauseLap();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	FTimespan StopLap();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void Reset();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	FTimespan GetCurrentTime();

};
