// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Stimulus.h"

#include "ExperimentController.generated.h"


UENUM()
enum class ETrialSelectionMode
{
	RandomExhaustive,
	Random,
	InOrder
};

UENUM(BlueprintType)
enum class EExperimentControllerState : uint8
{
	InTrial,
	BetweenTrials,
	BetweenBlocks,
	Finished,
	NotStarted,
	Error
};

UCLASS(Blueprintable, BlueprintType)
class PSYDEKICK_API AExperimentController : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AStimulus> StimulusClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AStimulus*> StimulusObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", UIMin = "1"))
	int32 NumberOfBlocks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TrialsPerBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETrialSelectionMode TrialSelectionMode;

	UPROPERTY(BlueprintReadOnly)
	int32 BlockID;
	
	UPROPERTY(BlueprintReadOnly)
	int32 TrialID;

	UPROPERTY(BlueprintReadOnly)
	EExperimentControllerState State = EExperimentControllerState::NotStarted;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStimulusConfiguration> ConfigurationClass;

	AExperimentController();

	UFUNCTION(BlueprintCallable, Category = "Psydekick")
	void AddConfiguration(UStimulusConfiguration* Configuration);

	UFUNCTION(BlueprintCallable, Category = "Psydekick")
	void InitializeBlocksFromCSV(FString Path);

	UFUNCTION(BlueprintCallable, Category = "Psydekick", Meta = (ExpandEnumAsExecs = "CurrentState"))
	void SwitchOnState(EExperimentControllerState &CurrentState);

	UFUNCTION(BlueprintCallable, Category = "Psydekick")
	void InitializeBlocks();

	UFUNCTION(BlueprintCallable, Category = "Psydekick")
	void NextTrial();

	UFUNCTION(BlueprintCallable, Category = "Psydekick")
	void EndTrial();

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick")
	void BlockStarted(int32 Block);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick")
	void BlockFinished(int32 Block);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick")
	void Finished();

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick")
	void TrialStarted(int32 Block, int32 Trial, UStimulusConfiguration* StimulusConfiguration);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick")
	void TrialFinished(int32 Block, int32 Trial, UStimulusConfiguration* StimulusConfiguration);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick")
	void StateChanged(EExperimentControllerState NewState);

protected:
	TArray<UStimulusConfiguration*> TrialConfigurations;
	TArray<TArray<UStimulusConfiguration*>> Blocks;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetState(EExperimentControllerState NewState);
	void StartTrial();
};




