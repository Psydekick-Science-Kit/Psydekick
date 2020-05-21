// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Queue.h"
#include "HAL/Runnable.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FileWriter.generated.h"

DECLARE_DYNAMIC_DELEGATE(FFileWriterShutdownComplete);

class PSYDEKICK_API FBackgroundFileWriter : public FRunnable
{
private:
	FString Path;
	FString ThreadName;
	TQueue<FString>* Buffer = NULL;
	bool KeepRunning = false;
	bool AbortNow = false;

public:
	FFileWriterShutdownComplete* OnComplete = NULL;
	FRunnableThread* Thread = NULL;

	void Initialize(FString InPath, TQueue<FString>* InBuffer);

	virtual uint32 Run();

	void KillThread(bool waitForIt = false);
	void Stop();
	void Abort();
};

UCLASS()
class PSYDEKICK_API UFileWriter : public UObject
{
	GENERATED_BODY()

private:
	FBackgroundFileWriter BgFileWriter;
	TQueue<FString> Buffer;

public:
	~UFileWriter();

	UPROPERTY(BlueprintReadOnly, Category = "Psydekick|File Writer")
	FString Filename = "";

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set filename"), Category = "Psydekick|File Writer")
	UFileWriter* Initialize(FString Path);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Write line"), Category = "Psydekick|File Writer")
	void WriteLine(FString Message);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|File Writer")
	void Shutdown(const FFileWriterShutdownComplete& OnComplete);
};
