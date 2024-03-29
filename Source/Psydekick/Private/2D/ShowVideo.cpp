// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "2D/ShowVideo.h"
#include "2D/PsydekickVisuals2D_BPLibrary.h"

#include "TimerManager.h"

void UShowVideo::ShowVideo(const UObject* WorldContextObject, UFileMediaSource* Video, const FVideoFinished& VideoFinished)
{
	UShowVideo* bpNode = UShowVideo::ShowVideoLatent(WorldContextObject, Video);

	bpNode->VideoFinishedExec.Add(VideoFinished);
	bpNode->Activate();
}

UShowVideo* UShowVideo::ShowVideoLatent(const UObject* WorldContextObject, UFileMediaSource* Video)
{
	UShowVideo* bpNode = NewObject<UShowVideo>();

	bpNode->WorldContextObject = WorldContextObject;
	bpNode->MediaPlayer->OpenSource(Video);

	return bpNode;
}

UShowVideo::UShowVideo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), WorldContextObject(nullptr)
{
	MediaPlayer = NewObject<UMediaPlayer>();
	MediaPlayer->OnEndReached.AddDynamic(this, &UShowVideo::OnFinished);
	MediaPlayer->AddToRoot();

	MediaTexture = NewObject<UMediaTexture>();
	MediaTexture->AutoClear = true;
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	MediaTexture->AddToRoot();

	SoundComponent = NewObject<UMediaSoundComponent>(GetTransientPackage(), NAME_None, RF_Transient | RF_Public);
	SoundComponent->bIsUISound = true;
	SoundComponent->SetMediaPlayer(MediaPlayer);
	SoundComponent->AddToRoot();
}

void UShowVideo::Activate()
{
	UPsydekickVisuals2D_BPLibrary::ShowImage(WorldContextObject, MediaTexture);

	float tickInterval = 0.01f; // @TODO: Figure out what this rate should *actually* be
	WorldContextObject->GetWorld()->GetTimerManager().SetTimer(AudioTickTimerHandle, SoundComponent, &UMediaSoundComponent::UpdatePlayer, tickInterval, true, 0);

	SoundComponent->Start();
	MediaPlayer->Play();
}

void UShowVideo::OnFinished()
{
	WorldContextObject->GetWorld()->GetTimerManager().ClearTimer(AudioTickTimerHandle);
	VideoFinishedExec.Broadcast();
}
