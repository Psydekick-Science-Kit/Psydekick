#include "CSVLoader.h"

#include "FileHelper.h"
#include "Internationalization/Regex.h" 

#include "Psydekick.h"

UCSVLoader* UCSVLoader::Load(FString Path)
{
	FRegexPattern CSVRegex("(?:,|\n|^)(\"(?:(?:\"\")*[^\"]*)*\"|[^\",\n]*|(?:\n|$))");

	TArray<FString> Lines;
	UE_LOG(LogPsydekick, Log, TEXT("UCSVLoader::Load Loading: %s"), *Path);
	bool Success = FFileHelper::LoadFileToStringArray(Lines, *Path);
	if (Success && Lines.Num() > 0)
	{
		for (int32 i=0; i<Lines.Num(); i++)
		{
			FString Line = Lines[i];
			TArray<FString> Record;
			FRegexMatcher FieldMatcher(CSVRegex, Line);

			while (FieldMatcher.FindNext())
			{
				FString Field = FieldMatcher.GetCaptureGroup(1);
				Field.TrimStartAndEndInline();

				if (Field.StartsWith("\"") && Field.EndsWith("\""))
				{
					Field = Field.Mid(1, Field.Len() - 2);
				}

				Record.Add(Field);
			}

			if (i==0)
			{
				Columns = Record;
			}
			else {
				Data.Add(Record);
			}
		}
	}
	else {
		UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::Load failed"));
	}

	return this;
}

int32 UCSVLoader::Num()
{
	return Data.Num();
}

TArray<FString> UCSVLoader::GetRow(int32 Index)
{
	if (Index >= 0 && Index < Data.Num())
	{
		return Data[Index];
	}
	else {
		UE_LOG(LogPsydekick, Error, TEXT("CSVLoader::GetRow Index %d out of range"), Index);
		return TArray<FString>();
	}
	
}

UObject* UCSVLoader::CreateObject(int32 Index, TSubclassOf<UObject> Class)
{
	UObject* Object = NewObject<UObject>(this, *Class);
	TArray<FString> Record = GetRow(Index);

	for (int32 i=0; i<Columns.Num(); i++)
	{
		FString Column = Columns[i];
		FName FieldName = FName(*Column);
		if (UProperty* Property = Class->FindPropertyByName(FieldName))
		{
			FString Value = Record[i];
			if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
			{
				Value = Value.ToLower();
				bool BoolValue = Value.Contains("t") || Value.Contains("1") || Value.Contains("y");
				BoolProperty->SetPropertyValue(Property->ContainerPtrToValuePtr<float>(Object), BoolValue);
			}
			else if (UIntProperty* IntProperty = Cast<UIntProperty>(Property))
			{
				int32 IntValue = FCString::Atoi(*Value);
				IntProperty->SetPropertyValue(Property->ContainerPtrToValuePtr<float>(Object), IntValue);
			}
			else if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(Property))
			{
				float FloatValue = FCString::Atof(*Value);
				FloatProperty->SetPropertyValue(Property->ContainerPtrToValuePtr<float>(Object), FloatValue);
			}
			else if (UStrProperty* StringProperty = Cast<UStrProperty>(Property))
			{
				StringProperty->SetPropertyValue(Property->ContainerPtrToValuePtr<float>(Object), Value);
			}
			else {
				UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::CreateObject unknown data type for %s. Only basic types are supported."), *Column);
			}
		}
		else {
			UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::CreateObject could not find property for field %s"), *Column);
		}
	}

	return Object;
}

void UCSVLoader::CreateObjects(TArray<UObject*>& Objects, TSubclassOf<UObject> Class)
{
	Objects.Empty();

	for (int32 Index = 0; Index < Num(); Index++)
	{
		Objects.Add(CreateObject(Index, Class));
	}
}
