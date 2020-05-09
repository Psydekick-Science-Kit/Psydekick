// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PsydekickBPLibrary.h"
#include "Psydekick.h"
#include "StimulusConfiguration.h"

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
