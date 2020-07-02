// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PsydekickBPLibrary.h"

#include "Data/ArrayPool.h"
#include "Flow/StimulusConfiguration.h"
#include "Engine/Engine.h"

#include "Psydekick.h"

UPsydekickBPLibrary::UPsydekickBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

FString UPsydekickBPLibrary::Conv_StimulusConfigurationToString(class UStimulusConfiguration* StimulusConfiguration)
{
	if (StimulusConfiguration)
	{
		return StimulusConfiguration->ToString();
	}
	else {
		return "";
	}
}

UArrayPool* UPsydekickBPLibrary::MakeArrayPool(TArray<UObject*> Source)
{
	UArrayPool* Pool = NewObject<UArrayPool>();
	Pool->SourcePool.Append(Source);

	return Pool;
}

TArray<UObject*> UPsydekickBPLibrary::MakeCombinationsOfObjects(TSubclassOf<UObject> Class, TMap<FName, FValueArrayWrapper> Arrays)
{
	UE_LOG(LogPsydekick, Log, TEXT("Making combinations of objects! %d arrays"), Arrays.Num());
	TArray<UObject*> Objects;

	// Determine total item count
	int32 ItemCount = 1;
	for (auto& Elem : Arrays)
	{
		UE_LOG(LogPsydekick, Log, TEXT("Array %s has %d items"), *Elem.Key.ToString(), Elem.Value.Array.Num());
		ItemCount *= Elem.Value.Array.Num();
	}

	UE_LOG(LogPsydekick, Log, TEXT("Going to construct %d items"), ItemCount);
	// Construct all items
	for(int32 Idx = 0; Idx < ItemCount; Idx++)
	{
		UObject* Object = NewObject<UObject>(GEngine->GetOuter(), *Class);
		Objects.Emplace(Object);
	}

	// Initialize item values
	int32 BlockSize = 1;
	for (auto& Elem : Arrays)
	{
		FName PropertyName = Elem.Key;
		TArray<UValueWrapper*> PropertyArray = Elem.Value.Array;
		for(int32 Idx = 0; Idx < ItemCount; Idx++)
		{
			UValueWrapper* ValueWrapper = PropertyArray[int(Idx/BlockSize) % PropertyArray.Num()];
			// set value
			// objects[idx][propertyName] = valuewrapper->value
			UObject* Object = Objects[Idx];
			if (UProperty* Property = Class->FindPropertyByName(PropertyName))
			{
				void* PropertyValuePtr = Property->ContainerPtrToValuePtr<void>(Object);

				if(UBooleanWrapper* BoolValueWrapper = Cast<UBooleanWrapper>(ValueWrapper))
				{
					if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
					{
						BoolProperty->SetPropertyValue(PropertyValuePtr, BoolValueWrapper->Value);
					}
					else
					{
						UE_LOG(LogPsydekick, Warning, TEXT("Property type mismatch - '%s' is not a bool on '%s'"), *PropertyName.ToString(), *Class->GetName());
					}
				}
			}
			else
			{
				UE_LOG(LogPsydekick, Warning, TEXT("Could not find property '%s' on class '%s'"), *PropertyName.ToString(), *Class->GetName());
			}
		}
		BlockSize *= PropertyArray.Num();
	}

	UE_LOG(LogPsydekick, Log, TEXT("Made %d objects!"), Objects.Num());
	return Objects;
}
