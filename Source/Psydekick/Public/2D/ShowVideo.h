// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "FileMediaSource.h" 
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h" 

#include "ShowVideo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVideoFinishedExec);
DECLARE_DYNAMIC_DELEGATE(FVideoFinished);

UCLASS()
class PSYDEKICK_API UShowVideo : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable, meta= (DisplayName = "Video Finished"))
	FVideoFinishedExec VideoFinishedExec;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject", DisplayName = "Show Video (latent)"), Category = "Psydekick|Visuals|2D")
	static UShowVideo* ShowVideoLatent(const UObject* WorldContextObject, UFileMediaSource* Video);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Psydekick|Visuals|2D")
	static void ShowVideo(const UObject* WorldContextObject, UFileMediaSource* Video, const FVideoFinished& VideoFinished);

	virtual void Activate() override;

private:
	const UObject* WorldContextObject;

	UMediaPlayer* MediaPlayer;
	UMediaTexture* MediaTexture;
	UMediaSoundComponent* SoundComponent;

	UFUNCTION()
	void OnFinished();

	FTimerHandle AudioTickTimerHandle;
};
