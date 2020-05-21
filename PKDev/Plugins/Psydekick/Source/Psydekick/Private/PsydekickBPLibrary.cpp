// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PsydekickBPLibrary.h"

#include "Data/ArrayPool.h"
#include "Flow/StimulusConfiguration.h"

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
