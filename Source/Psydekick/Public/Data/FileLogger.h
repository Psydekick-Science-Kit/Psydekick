// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"

#include "Data/FileWriter.h"

#include "FileLogger.generated.h"

UCLASS(BlueprintType)
class PSYDEKICK_API UFileLogger : public UFileWriter
{
	GENERATED_BODY()

public:

	UFileLogger* Initialize(FString Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log message"), Category = "Psydekick | Log")
	void Log(FString Message);
};
