// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PsydekickData.generated.h"

/**
 * 
 */
UCLASS()
class PSYDEKICK_API UPsydekickData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:

	static TMap<FString, UFileLogger*> CreateFileLoggerMap();
	static TMap<FString, UFileLogger*> FileLoggers;

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create a logger"), Category = "Psydekick | Data")
	static UFileLogger* CreateLogger(FString Name, FString Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get logger"), Category = "Psydekick | Data")
	static UFileLogger* GetLogger(FString Name);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log message"), Category = "Psydekick | Data")
	static bool Log(FString Name, FString message);
};
