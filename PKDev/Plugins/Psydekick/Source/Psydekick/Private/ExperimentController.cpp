// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperimentController.h"
#include "Engine/UserDefinedStruct.h"
#include "Math/UnrealMathUtility.h"

#include "Psydekick.h"
#include "Stimulus.h"
#include "CSVLoader.h"

// Sets default values
AExperimentController::AExperimentController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExperimentController::BeginPlay()
{
	Super::BeginPlay();

	if (StimulusObjects.Num() == 0)
	{
		if (!StimulusClass)
		{
			SetState(EExperimentControllerState::Error);
			UE_LOG(LogPsydekick, Warning, TEXT("No stimulus class specified - could not create stimulus object"));
		}
		else {
			const FVector Location = { 0, 20, 0 };
			const FRotator Rotation = FRotator(0, 0, 0);
			StimulusObjects.Add((AStimulus*)GetWorld()->SpawnActor(StimulusClass, &Location, &Rotation));
			UE_LOG(LogPsydekick, Log, TEXT("Spawned new stimulus object"));
		}
	}
}

void AExperimentController::InitializeBlocks()
{

	if (TrialSelectionMode == ETrialSelectionMode::InOrder)
	{
		int32 TrialCounter = 0;
		for (int32 i = 0; i < NumberOfBlocks; i++)
		{
			TArray<UStimulusConfiguration*> Block;
			for (int32 j = 0; j < TrialsPerBlock; j++)
			{
				Block.Add(TrialConfigurations[(TrialCounter++) % TrialConfigurations.Num()]);
			}
			Blocks.Add(Block);
		}
	}
	else if (TrialSelectionMode == ETrialSelectionMode::Random) {
		for (int32 i = 0; i < NumberOfBlocks; i++)
		{
			TArray<UStimulusConfiguration*> Block;
			for (int32 j = 0; j < TrialsPerBlock; j++)
			{
				Block.Add(TrialConfigurations[FMath::RandRange(0, TrialConfigurations.Num() - 1)]);
			}
			Blocks.Add(Block);
		}
	}
	else if (TrialSelectionMode == ETrialSelectionMode::RandomExhaustive) {
		TArray<UStimulusConfiguration*> Pool;

		for (int32 i = 0; i < NumberOfBlocks; i++)
		{
			TArray<UStimulusConfiguration*> Block;
			for (int32 j = 0; j < TrialsPerBlock; j++)
			{
				if (Pool.Num() == 0) {
					Pool.Append(TrialConfigurations);
				}

				int32 Idx = FMath::RandRange(0, Pool.Num() - 1);
				Block.Add(Pool[Idx]);
				Pool.RemoveAt(Idx);
			}
			Blocks.Add(Block);
		}
	}

	UE_LOG(LogPsydekick, Log, TEXT("Block and trial order:"));
	for (int32 i = 0; i < Blocks.Num(); i++)
	{
		for (int32 j = 0; j < Blocks[i].Num(); j++)
		{
			UE_LOG(LogPsydekick, Log, TEXT("\tBlock=%d,Trial=%d,Stimulus=<%s>"), i, j, *Blocks[i][j]->ToString());
		}
	}

	BlockID = 0;
	TrialID = 0;
}

void AExperimentController::AddConfiguration(UStimulusConfiguration* Configuration)
{
	TrialConfigurations.Add(Configuration);
}

void AExperimentController::InitializeBlocksFromCSV(FString Path)
{
	if (!ConfigurationClass)
	{
		UE_LOG(LogPsydekick, Warning, TEXT("ExperimentController::InitializeBlocksFromCSV ConfigurationClass is not set"))
		return;
	}

	UCSVLoader* Loader = NewObject<UCSVLoader>();
	TArray<UObject*> TmpObjects;

	TrialConfigurations.Empty();

	Loader->Load(Path);
	Loader->CreateObjects(TmpObjects, ConfigurationClass);
	
	for (auto Object : TmpObjects)
	{
		if (UStimulusConfiguration* ConfigObject = Cast<UStimulusConfiguration>(Object))
		{
			TrialConfigurations.Emplace(ConfigObject);
		}
	}

	InitializeBlocks();
}

void AExperimentController::NextTrial()
{
	if (BlockID >= Blocks.Num())
	{
		SetState(EExperimentControllerState::Error);
		UE_LOG(LogPsydekick, Warning, TEXT("ExperimentController::NextTrial No more blocks"));
	}
	else {
		if (TrialID == 0)
		{
			BlockStarted(BlockID);
		}

		SetState(EExperimentControllerState::InTrial);
		UStimulusConfiguration* StimulusConfiguration = Blocks[BlockID][TrialID];

		TrialStarted(BlockID, TrialID, StimulusConfiguration);
		for (auto& StimulusObject : StimulusObjects)
		{
			StimulusObject->NewConfiguration(StimulusConfiguration);
		}
	}
}

void AExperimentController::EndTrial()
{
	bool DoneWithBlock = false;
	bool DoneWithAllBlocks = false;

	EExperimentControllerState NewState;
	UStimulusConfiguration* CurrentConfig = Blocks[BlockID][TrialID];

	if (++TrialID >= Blocks[BlockID].Num())
	{
		DoneWithBlock = true;

		if (++BlockID >= Blocks.Num())
		{
			NewState = EExperimentControllerState::Finished;
			DoneWithAllBlocks = true;
		}
		else {
			NewState = EExperimentControllerState::BetweenBlocks;
		}
		TrialID = 0;
	}
	else {
		NewState = EExperimentControllerState::BetweenTrials;
	}

	SetState(NewState);
	TrialFinished(BlockID, TrialID, CurrentConfig);
	if (DoneWithBlock)
	{
		BlockFinished(BlockID);
	}
	if (DoneWithAllBlocks)
	{
		Finished();
	}

	for (auto& StimulusObject : StimulusObjects)
	{
		StimulusObject->Reset();
	}
}

void AExperimentController::SetState(EExperimentControllerState NewState)
{
	State = NewState;
	StateChanged(State);
}

void AExperimentController::SwitchOnState(EExperimentControllerState& CurrentState)
{
	CurrentState = State;
}