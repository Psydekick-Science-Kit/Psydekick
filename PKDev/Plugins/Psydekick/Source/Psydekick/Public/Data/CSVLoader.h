// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSVLoader.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PSYDEKICK_API UCSVLoader : public UObject
{
	GENERATED_BODY()


protected:
	TArray<TArray<FString>> Data;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Psydekick|Data")
	TArray<FString> Columns;

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	UCSVLoader* Load(FString Path);

	UFUNCTION(BlueprintPure, Category = "Psydekick|Data")
	int32 Num();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	TArray<FString> GetRow(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	UObject* CreateObject(int32 Index, TSubclassOf<UObject> Class);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void CreateObjects(TArray<UObject*>& Objects, TSubclassOf<UObject> Class);
};
