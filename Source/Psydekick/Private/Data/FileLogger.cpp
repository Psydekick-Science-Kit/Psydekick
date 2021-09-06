// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "Data/FileLogger.h"

#include "Misc/DateTime.h"

UFileLogger* UFileLogger::Initialize(FString Path)
{
	UFileWriter::Initialize(Path);
	Log("Log started " + Filename);

	return this;
}

void UFileLogger::Log(FString Message)
{
	FString Timestamp = FString::Printf(TEXT("%f"), FPlatformTime::Seconds());

	this->WriteLine(FDateTime::Now().ToIso8601() + "\t" + Timestamp + "\t" + Message);
}