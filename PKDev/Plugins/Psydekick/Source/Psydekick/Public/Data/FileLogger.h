// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/FileWriter.h"

#include "FileLogger.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PSYDEKICK_API UFileLogger : public UFileWriter
{
	GENERATED_BODY()

public:

	UFileLogger* Initialize(FString Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log message"), Category = "Psydekick | Log")
	void Log(FString Message);
};
