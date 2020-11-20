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

public:
	void LogObjectProperties(const UObject* Object, const UStruct* Class, const void* ContainerPtr);

	UPROPERTY(BlueprintReadWrite, BlueprintSetter=SetFieldNames, Category="General")
	TArray<FString> FieldNames;

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void SetFieldNames(const TArray<FString> InFieldNames);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void SetFieldNamesFromObject(const UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data", CustomThunk, meta = (CustomStructureParam = "Struct"))
	void SetFieldNamesFromStruct(const TFieldPath<FProperty> Struct);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void LogStrings(const TMap<FString,FString> Record);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data")
	void LogObject(const UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Data", CustomThunk, meta = (CustomStructureParam = "Struct"))
	void LogStruct(const TFieldPath<FProperty> Struct);

	DECLARE_FUNCTION(execSetFieldNamesFromStruct)
	{
		Stack.Step(Stack.Object, NULL);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		FStructProperty* StructProperty = ExactCastField<FStructProperty>(Stack.MostRecentProperty);
		P_FINISH;

		UScriptStruct* ScriptStruct = StructProperty->Struct;
		P_THIS->SetFieldNamesFromObject(ScriptStruct);
	}

	DECLARE_FUNCTION(execLogStruct)
	{
		Stack.Step(Stack.Object, NULL);
		void* StructPtr = Stack.MostRecentPropertyAddress;
		FStructProperty* StructProperty = ExactCastField<FStructProperty>(Stack.MostRecentProperty);
		P_FINISH;

		UScriptStruct* ScriptStruct = StructProperty->Struct;
		if (P_THIS->FieldNames.Num() == 0)
		{
			P_THIS->SetFieldNamesFromObject(ScriptStruct);
		}

		P_THIS->LogObjectProperties(ScriptStruct, ScriptStruct, StructPtr);
	}
};
