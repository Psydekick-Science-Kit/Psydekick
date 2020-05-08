// Fill out your copyright notice in the Description page of Project Settings.

#include "PsydekickData.h"

#include "Misc/Paths.h" 

#include "Psydekick.h"
#include "FileLogger.h"

TMap<FString, UFileLogger*> UPsydekickData::FileLoggers = UPsydekickData::CreateFileLoggerMap();
TMap<FString, UFileLogger*> UPsydekickData::CreateFileLoggerMap()
{
	TMap<FString, UFileLogger*> LoggerMap;
	return LoggerMap;
}

UFileLogger* UPsydekickData::CreateLogger(FString Name, FString ParentPath)
{

	#if PLATFORM_WINDOWS
		bool PathIsAbsolute = ParentPath.Contains(":");
	#else
		bool PathIsAbsolute = ParentPath.StartsWith("/");
	#endif

	if (!PathIsAbsolute)
	{
		ParentPath = FPaths::ProjectLogDir() + "/" + ParentPath;
	}
	
	if(!ParentPath.EndsWith("/"))
	{
		ParentPath += "/";
	}

	FPaths::NormalizeDirectoryName(ParentPath);
	FPaths::RemoveDuplicateSlashes(ParentPath);

	FString Path = ParentPath + Name + "-" + FDateTime::Now().ToString() + ".log";

	UFileLogger* Logger = NewObject<UFileLogger>();

	Logger->Initialize(Path);
	UPsydekickData::FileLoggers.Add(Name, Logger);

	return Logger;
}

UFileLogger* UPsydekickData::GetLogger(FString Name)
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

bool UPsydekickData::Log(FString LoggerName, FString Message)
{
	UFileLogger* Logger = UPsydekickData::GetLogger(LoggerName);
	if (Logger != NULL) {
		Logger->Log(Message);
		return true;
	}

	return false;
}