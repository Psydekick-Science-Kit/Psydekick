// (c) 2021 Dominic Canare <dom@dominiccanare.com>


#include "3D/ActorMovementController.h"

#include "Psydekick.h"

#include "GameFramework/Character.h"
#include "WheeledVehicle.h"
#include "WheeledVehicleMovementComponent.h"

// Sets default values for this component's properties
UActorMovementController::UActorMovementController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogPsydekick, Log, TEXT("MovementController Constructed"));

	// ...
}


// Called when the game starts
void UActorMovementController::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UActorMovementController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetOwner();
	ACharacter* Character = Cast<ACharacter>(Actor);
	if (Character != nullptr)
	{
		if (IShouldStop) {

		}
		else {
			Character->AddMovementInput(Heading);
		}

		return;
	}
	AWheeledVehicle* Vehicle = Cast<AWheeledVehicle>(Actor);
	if (Vehicle != nullptr)
	{
		if (IShouldStop) {
			Vehicle->GetVehicleMovement()->SetBrakeInput(1.0);
		}
		else {
			Vehicle->GetVehicleMovement()->SetThrottleInput(Heading.X);
			Vehicle->GetVehicleMovement()->SetSteeringInput(Heading.Y);
		}
	}
}

void UActorMovementController::MoveInDirection(FVector Direction)
{
	Heading = Direction;
	IShouldStop = false;
}

void UActorMovementController::Stop()
{
	IShouldStop = true;
}
