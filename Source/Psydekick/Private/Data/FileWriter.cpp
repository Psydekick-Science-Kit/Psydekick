// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "Data/FileWriter.h"

#include "Psydekick.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"

UFileWriter::~UFileWriter()
{
	UE_LOG(LogPsydekick, Log, TEXT("UFileWriter destructor"));
	if (BgFileWriter.Thread != NULL)
	{
		BgFileWriter.Abort();
	}
}

UFileWriter* UFileWriter::Initialize(FString Path)
{
	Filename = FPaths::ConvertRelativePathToFull(Path);

	bool DirectoryOK = FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*FPaths::GetPath(Filename));

	if (!DirectoryOK)
	{
		UE_LOG(LogPsydekick, Error, TEXT("UFileWriter::Initalize Failed to find/create directory!"));
	}

	BgFileWriter.Initialize(Filename, &Buffer);

	return this;
}

void UFileWriter::WriteLine(FString Line)
{
	Buffer.Enqueue(Line);
}

void UFileWriter::Shutdown(const FFileWriterShutdownComplete& OnComplete)
{
	BgFileWriter.OnComplete = new FFileWriterShutdownComplete(OnComplete);
	BgFileWriter.KillThread(false);
}

void FBackgroundFileWriter::Initialize(FString InPath, TQueue<FString>* InBuffer)
{
	Path = InPath;
	Buffer = InBuffer;

	ThreadName = FString::Printf(TEXT("FBackgroundFileWriter-%s"), *Path);
	Thread = FRunnableThread::Create(this, *ThreadName, 0);
}

void FBackgroundFileWriter::KillThread(bool WaitForIt)
{
	if (Thread != NULL && KeepRunning)
	{
		Thread->Kill(WaitForIt);
		if (WaitForIt)
		{
			Thread->WaitForCompletion();
		}
	}
}

void FBackgroundFileWriter::Stop()
{
	KeepRunning = false;
	FRunnable::Stop();
}

uint32 FBackgroundFileWriter::Run()
{
	UE_LOG(LogPsydekick, Verbose, TEXT("FBackgroundFileWriter::Run Starting thread '%s'"), *Path);
	KeepRunning = true;

	FString Line;
	while (!AbortNow && KeepRunning)
	{
		while (!AbortNow && Buffer->Dequeue(Line))
		{
			FFileHelper::SaveStringToFile(
				Line + "\n",
				*Path,
				FFileHelper::EEncodingOptions::AutoDetect,
				&IFileManager::Get(),
				EFileWrite::FILEWRITE_Append
			);
		}
		// sleep?
		FPlatformProcess::Sleep(1.0f / 30.0f);
	}

	if (OnComplete != NULL)
	{
		FFileWriterShutdownComplete* Callback = OnComplete;
		AsyncTask(ENamedThreads::GameThread, [Callback]()
			{
				(*Callback).ExecuteIfBound();
			}
		);
	}

	return 0;
}

void FBackgroundFileWriter::Abort()
{
	AbortNow = true;
	KillThread(true);
}
