// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/PsydekickData.h"

#include "Data/FileLogger.h"
#include "Data/CSVLoader.h"

#include "Psydekick.h"
#include "Misc/Paths.h"

TMap<FString, UFileLogger*> UPsydekickData::FileLoggers = UPsydekickData::CreateFileLoggerMap();
TMap<FString, UFileLogger*> UPsydekickData::CreateFileLoggerMap()
{
	TMap<FString, UFileLogger*> LoggerMap;
	return LoggerMap;
}

TMap<FString, UCSVLogger*> UPsydekickData::CSVLoggers = UPsydekickData::CreateCSVLoggerMap();
TMap<FString, UCSVLogger*> UPsydekickData::CreateCSVLoggerMap()
{
	TMap<FString, UCSVLogger*> LoggerMap;
	return LoggerMap;
}

UFileLogger* UPsydekickData::CreateLogger(const FString Name, const FString FolderPath)
{
	#if PLATFORM_WINDOWS
		bool PathIsAbsolute = FolderPath.Contains(":");
	#else
		bool PathIsAbsolute = FolderPath.StartsWith("/");
	#endif

	FString Path;
	if (!PathIsAbsolute)
	{
		Path = FPaths::ProjectLogDir() + "/" + FolderPath;
	}
	else
	{
		Path = FolderPath;
	}


	FPaths::NormalizeDirectoryName(Path);
	FPaths::RemoveDuplicateSlashes(Path);

	if(!Path.EndsWith("/"))
	{
		Path += "/";
	}

	Path += Name + "-" + FDateTime::Now().ToString() + ".log";

	UFileLogger* Logger = NewObject<UFileLogger>();

	Logger->Initialize(Path);
	UPsydekickData::FileLoggers.Add(Name, Logger);

	return Logger;
}

UFileLogger* UPsydekickData::GetLogger(const FString Name)
{
	UFileLogger* Logger = NULL;

	if (UPsydekickData::FileLoggers.Contains(Name))
	{
		Logger = *UPsydekickData::FileLoggers.Find(Name);
	} else {
		UE_LOG(LogPsydekick, Error, TEXT("UPsydekickData.GetLogger: Could not find logger: '%s'"), *Name);
	}

	return Logger;
}

bool UPsydekickData::Log(const FString Name, const FString Message)
{
	UFileLogger* Logger = UPsydekickData::GetLogger(Name);
	if (Logger != NULL) {
		Logger->Log(Message);
		return true;
	}

	return false;
}

UCSVLogger* UPsydekickData::CreateCSVLogger(const FString Name, const FString FolderPath)
{
	#if PLATFORM_WINDOWS
		bool PathIsAbsolute = FolderPath.Contains(":");
	#else
		bool PathIsAbsolute = FolderPath.StartsWith("/");
	#endif

	FString Path;
	if (!PathIsAbsolute)
	{
		Path = FPaths::ProjectLogDir() + "/" + FolderPath;
	}
	else
	{
		Path = FolderPath;
	}

	FPaths::NormalizeDirectoryName(Path);
	FPaths::RemoveDuplicateSlashes(Path);

	if(!Path.EndsWith("/"))
	{
		Path += "/";
	}

	Path += Name + "-" + FDateTime::Now().ToString() + ".csv";

	UCSVLogger* Logger = NewObject<UCSVLogger>();

	Logger->Initialize(Path);
	UPsydekickData::CSVLoggers.Add(Name, Logger);

	return Logger;
}

UCSVLogger* UPsydekickData::GetCSVLogger(const FString Name)
{
	UCSVLogger* Logger = NULL;

	if (UPsydekickData::CSVLoggers.Contains(Name))
	{
		Logger = *UPsydekickData::CSVLoggers.Find(Name);
	} else {
		UE_LOG(LogPsydekick, Error, TEXT("UPsydekickData.GetCSVLogger: Could not find CSV logger: '%s'"), *Name);
	}

	return Logger;
}

bool UPsydekickData::LogDataStrings(const FString Name, const TMap<FString, FString> Record)
{
	UE_LOG(LogPsydekick, Log, TEXT("Logging strings!"));
	UCSVLogger* Logger = UPsydekickData::GetCSVLogger(Name);
	if (Logger != NULL) {
		UE_LOG(LogPsydekick, Log, TEXT("Sending the stuff"));
		Logger->LogStrings(Record);
		return true;
	}

	return false;
}

bool UPsydekickData::LogDataObject(const FString Name, const UObject* Object)
{
	UCSVLogger* Logger = UPsydekickData::GetCSVLogger(Name);
	if (Logger != NULL) {
		Logger->LogObject(Object);
		return true;
	}

	return false;
}

void UPsydekickData::CreateObjectsFromCSV(TArray<UObject*>& Result, FString Path, TSubclassOf<UObject> Class)
{
	UCSVLoader* Loader = NewObject<UCSVLoader>();
	Loader->Load(Path);
	Loader->CreateObjects(Result, Class);
}