// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "FileMediaSource.h" 
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h" 

#include "ShowVideo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVideoFinished);

/**
 * 
 */
UCLASS()
class PSYDEKICK_API UShowVideo : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FVideoFinished VideoFinished;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Psydekick|Visuals|2D")
	static UShowVideo* ShowVideo(const UObject* WorldContextObject, UFileMediaSource* Video);

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
