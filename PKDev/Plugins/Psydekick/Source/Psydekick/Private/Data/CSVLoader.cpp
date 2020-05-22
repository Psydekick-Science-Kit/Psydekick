#include "Data/CSVLoader.h"

#include "Psydekick.h"

#include "Misc/FileHelper.h"
#include "Internationalization/Regex.h"
#include "Engine/StaticMesh.h"

UCSVLoader* UCSVLoader::Load(FString Path)
{
	FRegexPattern CSVRegex("(?:,|\n|^)(\"(?:(?:\"\")*[^\"]*)*\"|[^\",\n]*|(?:\n|$))");

	TArray<FString> Lines;
	UE_LOG(LogPsydekick, Log, TEXT("UCSVLoader::Load Loading: %s"), *Path);
	bool Success = FFileHelper::LoadFileToStringArray(Lines, *Path);
	if (Success)
	{
		if (Lines.Num() == 0)
		{
			UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::Load Empty file"));
		}

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
			void* PropertyValuePtr = Property->ContainerPtrToValuePtr<void>(Object);

			if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
			{
				Value = Value.ToLower();
				bool BoolValue = Value.Contains("t") || Value.Contains("1") || Value.Contains("y");
				BoolProperty->SetPropertyValue(PropertyValuePtr, BoolValue);
			}
			else if (UIntProperty* IntProperty = Cast<UIntProperty>(Property))
			{
				int32 IntValue = FCString::Atoi(*Value);
				IntProperty->SetPropertyValue(PropertyValuePtr, IntValue);
			}
			else if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(Property))
			{
				float FloatValue = FCString::Atof(*Value);
				FloatProperty->SetPropertyValue(PropertyValuePtr, FloatValue);
			}
			else if (UStrProperty* StringProperty = Cast<UStrProperty>(Property))
			{
				StringProperty->SetPropertyValue(PropertyValuePtr, Value);
			}
			else if (UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property))
			{
				FString CPPType = Property->GetCPPType();
				UE_LOG(LogPsydekick, Log, TEXT("UCSVLoader::CreateObject Got an object type for %s (%s)"), *Column, *CPPType);
				if(CPPType == "UStaticMesh*")
				{
					FStringAssetReference assetRef(Value);
					if(UStaticMesh* StaticMesh = Cast<UStaticMesh>(assetRef.TryLoad()))
					{
						ObjectProperty->SetObjectPropertyValue(PropertyValuePtr, StaticMesh);
					}
					else
					{
						UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::CreateObject Failed to load StaticMesh \"%s\" for %s"), *Value, *Column);
					}
				}
				else
				{
					UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::CreateObject Unsupported object property %s for field %s"), *CPPType, *Column);
				}

			}
			else if (UStructProperty* StructProperty = Cast<UStructProperty>(Property))
			{
				UScriptStruct* ScriptStruct = StructProperty->Struct;
				FString CPPType = ScriptStruct->GetStructCPPName();
				UE_LOG(LogPsydekick, Log, TEXT("UCSVLoader::CreateObject Got an struct type for %s (%s)"), *Column, *CPPType);
				if (CPPType == "FLinearColor")
				{
					FLinearColor* ColorStruct = (FLinearColor*)PropertyValuePtr;
					*ColorStruct = (FColor::FromHex(Value)).ReinterpretAsLinear();
				}
				else
				{
					UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::CreateObject unknown struct type %s for %s."), *CPPType, *Column);
				}
			}
			else
			{
				UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::CreateObject unknown data type for %s. Only basic types are supported."), *Column);
			}
		}
		else {
			UE_LOG(LogPsydekick, Warning, TEXT("UCSVLoader::CreateObject could not find property for field %s in %s"), *Column, *Object->GetFName().ToString());
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
