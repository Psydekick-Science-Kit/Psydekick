// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Flow/Stimulus.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psydekick|Flow")
	TSubclassOf<AStimulus> StimulusClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psydekick|Flow")
	TArray<AStimulus*> StimulusObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psydekick|Flow", meta = (ClampMin = "1", UIMin = "1"))
	int32 NumberOfBlocks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psydekick|Flow")
	int32 TrialsPerBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Psydekick|Flow")
	ETrialSelectionMode TrialSelectionMode;

	UPROPERTY(BlueprintReadOnly, Category = "Psydekick|Flow")
	int32 BlockID;

	UPROPERTY(BlueprintReadOnly, Category = "Psydekick|Flow")
	int32 TrialID;

	UPROPERTY(BlueprintReadOnly, Category = "Psydekick|Flow")
	EExperimentControllerState State = EExperimentControllerState::NotStarted;

	UPROPERTY(EditDefaultsOnly, Category = "Psydekick|Flow")
	TSubclassOf<UStimulusConfiguration> ConfigurationClass;

	AExperimentController();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Flow")
	void AddConfiguration(UStimulusConfiguration* Configuration);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Flow")
	void InitializeBlocksFromCSV(FString Path, int32 &ConfigurationCount);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Flow", Meta = (ExpandEnumAsExecs = "CurrentState"))
	void SwitchOnState(EExperimentControllerState &CurrentState);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Flow")
	void InitializeBlocks();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Flow")
	void NextTrial();

	UFUNCTION(BlueprintCallable, Category = "Psydekick|Flow")
	void EndTrial();

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick|Flow")
	void BlockStarted(int32 Block);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick|Flow")
	void BlockFinished(int32 Block);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick|Flow")
	void Finished();

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick|Flow")
	void TrialStarted(int32 Block, int32 Trial, UStimulusConfiguration* StimulusConfiguration);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick|Flow")
	void TrialFinished(int32 Block, int32 Trial, UStimulusConfiguration* StimulusConfiguration);

	UFUNCTION(BlueprintImplementableEvent, Category = "Psydekick|Flow")
	void StateChanged(EExperimentControllerState NewState);

protected:
	TArray<UStimulusConfiguration*> TrialConfigurations;
	TArray<TArray<UStimulusConfiguration*>> Blocks;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetState(EExperimentControllerState NewState);
	void StartTrial();
};




