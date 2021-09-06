// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "Data/FileLogger.h"
#include "Data/CSVLogger.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "PsydekickData.generated.h"

UCLASS()
class PSYDEKICK_API UPsydekickData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:

	static TMap<FString, UFileLogger*> CreateFileLoggerMap();
	static TMap<FString, UFileLogger*> FileLoggers;
	static TMap<FString, UCSVLogger*> CreateCSVLoggerMap();
	static TMap<FString, UCSVLogger*> CSVLoggers;

public:
	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static void CreateObjectsFromCSV(TArray<UObject*>& Result, FString Path, TSubclassOf<UObject> Class);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static UFileLogger* CreateLogger(const FString Name, const FString FolderPath);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static UFileLogger* GetLogger(const FString Name);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static bool Log(const FString Name, const FString message);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static UCSVLogger* CreateCSVLogger(const FString Name, const FString FolderPath);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static UCSVLogger* GetCSVLogger(const FString Name);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static bool LogDataStrings(const FString Name, const TMap<FString, FString> Record);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	static bool LogDataObject(const FString Name, const UObject* Object);
};
