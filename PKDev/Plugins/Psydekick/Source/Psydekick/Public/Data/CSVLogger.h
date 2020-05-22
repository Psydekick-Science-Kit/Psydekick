// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/FileWriter.h"
#include "Psydekick.h"

#include "CSVLogger.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class PSYDEKICK_API UCSVLogger : public UFileWriter
{
	GENERATED_BODY()

private:
	void LogObjectProperties(UObject* Object, UStruct* Class, void* ContainerPtr);

public:
	UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetFieldNames)
	TArray<FString> FieldNames;

	UFUNCTION(BlueprintCallable)
	void SetFieldNames(TArray<FString> InFieldNames);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void SetFieldNamesFromObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data", CustomThunk, meta = (CustomStructureParam = "Struct"))
	void SetFieldNamesFromStruct(UProperty* Struct);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void LogStrings(TMap<FString,FString> Record);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void LogObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data", CustomThunk, meta = (CustomStructureParam = "Struct"))
	void LogStruct(UProperty* Struct);

	DECLARE_FUNCTION(execSetFieldNamesFromStruct)
	{
		Stack.Step(Stack.Object, NULL);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		P_FINISH;

		UScriptStruct* ScriptStruct = StructProperty->Struct;
		P_THIS->SetFieldNamesFromObject(ScriptStruct);
	}

	DECLARE_FUNCTION(execLogStruct)
	{
		Stack.Step(Stack.Object, NULL);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		P_FINISH;

		UScriptStruct* ScriptStruct = StructProperty->Struct;
		if (P_THIS->FieldNames.Num() == 0)
		{
			P_THIS->SetFieldNamesFromObject(ScriptStruct);
		}

		P_THIS->LogObjectProperties(ScriptStruct, ScriptStruct, StructPtr);
	}
};
