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

FString UPsydekickBPLibrary::GetProjectSetting(FString Name)
{
	FString Value;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		*Name,
		Value,
		GGameIni
	);

	return Value;
}

FString UPsydekickBPLibrary::GetBuildDate()
{
	FString MacroDate = TEXT(__DATE__); // Jan 02 3456

	FString Year = *MacroDate.Mid(7, 4);
	FString Day = *MacroDate.Mid(4, 2).TrimStartAndEnd();

	int32 Month = 0;

	FString MonthAbbr = MacroDate.Left(3);
	if (MonthAbbr.Equals("Jan")) Month = 1;
	else if (MonthAbbr.Equals("Feb")) Month = 2;
	else if (MonthAbbr.Equals("Mar")) Month = 3;
	else if (MonthAbbr.Equals("Apr")) Month = 4;
	else if (MonthAbbr.Equals("May")) Month = 5;
	else if (MonthAbbr.Equals("Jun")) Month = 6;
	else if (MonthAbbr.Equals("Jul")) Month = 7;
	else if (MonthAbbr.Equals("Aug")) Month = 8;
	else if (MonthAbbr.Equals("Sep")) Month = 9;
	else if (MonthAbbr.Equals("Oct")) Month = 10;
	else if (MonthAbbr.Equals("Nov")) Month = 11;
	else if (MonthAbbr.Equals("Dec")) Month = 12;

	return FString::Printf(TEXT("%s-%02d-%02s"), *Year, Month, *Day);
}

FString UPsydekickBPLibrary::GetBuildTime()
{
	return TEXT(__TIME__);
}

FString UPsydekickBPLibrary::GetBuildString()
{
	FString Version = GetProjectSetting(TEXT("ProjectVersion"));
	FString Date = GetBuildDate().Replace(TEXT("-"), TEXT(""));
	FString Time = GetBuildTime().Replace(TEXT(":"), TEXT(""));

	return FString::Printf(TEXT("v%s_%s_%s"), *Version, *Date, *Time);
}
