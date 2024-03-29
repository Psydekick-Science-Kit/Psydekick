// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Flow/StimulusConfiguration.h"

#include "Stimulus.generated.h"

UCLASS()
class PSYDEKICK_API AStimulus : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStimulus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void NewConfiguration(UStimulusConfiguration* Configuration);

};
