// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/CSVLogger.h"
#include "Psydekick.h"

#include "Misc/DateTime.h"

void UCSVLogger::SetFieldNames(const TArray<FString> InFieldNames)
{
	if(FieldNames.Num() > 0)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("UCSVLogger::SetFieldNames Cannot change field names after headers are written."));
		return;
	}

	if (!InFieldNames.Contains("Timestamp")) {
		FieldNames.Insert("Timestamp", 0);
	}
	FieldNames.Append(InFieldNames);

	FString HeaderLine = "";
	for (FString FieldName : FieldNames) {
		HeaderLine.Append(FieldName + ",");
	}
	HeaderLine.RemoveFromEnd(",");
	WriteLine(HeaderLine);
}

void UCSVLogger::SetFieldNamesFromObject(const UObject* Object)
{
	if(!Object){
		return;
	}

	TArray<FString> Fields;

	const UStruct* Class = Cast<UScriptStruct>(Object);
	if(!Class)
	{
		Class = Object->GetClass();
	}

	for (TFieldIterator<UProperty> PropertyItr(Class); PropertyItr; ++PropertyItr)
	{
		UProperty* Property = *PropertyItr;
		Fields.Emplace(Property->GetDisplayNameText().ToString());
	}
	SetFieldNames(Fields);
}

void UCSVLogger::LogStrings(const TMap<FString,FString> Record)
{

	UE_LOG(LogPsydekick, Log, TEXT("Got some strings yo!"));
	if (FieldNames.Num() == 0)
	{
		TArray<FString> Keys;
		Record.GetKeys(Keys);
		SetFieldNames(Keys);
	}

	FString Line = "";
	if (!Record.Contains("Timestamp")) {
		FString Timestamp = FDateTime::Now().ToIso8601();
		Line += Timestamp + ",";
	}

	for (FString FieldName : FieldNames) {
		FString Value;
		if (Record.Contains(FieldName)) {
			Value = *Record.Find(FieldName);
		} else {
			Value = "";
		}

		Line += Value + ",";
	}
	Line.RemoveFromEnd(",");

	WriteLine(Line);
}

void UCSVLogger::LogObject(const UObject* Object)
{
	if(!Object){
		return;
	}

	if (FieldNames.Num() == 0)
	{
		SetFieldNamesFromObject(Object);
	}

	LogObjectProperties(Object, Object->GetClass(), Object);
}

void UCSVLogger::LogObjectProperties(const UObject* Object, const UStruct* Class, const void* ContainerPtr)
{
	TMap<FString, FString> FieldValues;

	for (FString FieldName : FieldNames) {
		UProperty* Property = Class->FindPropertyByName(FName(*FieldName));
		if(!Property)
		{
			Property = Class->CustomFindProperty(FName(*FieldName));
		}

		if (Property)
		{
			FString Value = "";
			const void* PropertyValuePtr = Property->ContainerPtrToValuePtr<void>(ContainerPtr);

			if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
			{
				Value = BoolProperty->GetPropertyValue(PropertyValuePtr) ? "1" : "0";
			}
			else if (UIntProperty* IntProperty = Cast<UIntProperty>(Property))
			{
				Value = FString::FromInt(IntProperty->GetPropertyValue(PropertyValuePtr));
			}
			else if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(Property))
			{
				Value = FString::SanitizeFloat(FloatProperty->GetPropertyValue(PropertyValuePtr));
			}
			else if (UStrProperty* StringProperty = Cast<UStrProperty>(Property))
			{
				Value = StringProperty->GetPropertyValue(PropertyValuePtr);
			}
			else if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
			{
				UE_LOG(LogPsydekick, Warning, TEXT("UCSVLogger::LogObject Unsupported Object property %s"), *FieldName);
				Value = "<Object>";
			}
			else if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
			{
				UE_LOG(LogPsydekick, Warning, TEXT("UCSVLogger::LogObject Unsupported Struct property %s"), *FieldName);
				Value = "<Struct>";
				//UScriptStruct* ScriptStruct = StructProperty->Struct;
			}
			else
			{
				UE_LOG(LogPsydekick, Warning, TEXT("UCSVLogger::LogObject Unsupported property %s"), *FieldName);
				Value = "?";
			}

			FieldValues.Add(FieldName, Value);
		}
		else
		{
			if (FieldName != "Timestamp")
			{
				UE_LOG(LogPsydekick, Warning, TEXT("UCSVLogger::LogObject Object has no property %s"), *FieldName);
			}
		}
	}

	LogStrings(FieldValues);
}
