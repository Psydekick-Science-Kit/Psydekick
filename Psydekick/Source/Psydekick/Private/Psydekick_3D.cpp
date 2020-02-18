// Fill out your copyright notice in the Description page of Project Settings.


#include "Psydekick_3D.h"
#include "Psydekick.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/World.h" 
#include "Materials/MaterialInstanceDynamic.h" 
#include "GameFramework/PlayerController.h" 

#include "ActorMovementController.h" 


AStaticMeshActor* UPsydekick_3D::SpawnMesh(const UObject* WorldContextObject, UStaticMesh* Mesh, FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnParams;
	AStaticMeshActor* Actor = WorldContextObject->GetWorld()->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(),
		Location,
		Rotation,
		SpawnParams
	);
	
	UStaticMeshComponent* Component = Actor->GetStaticMeshComponent();
	Component->SetMobility(EComponentMobility::Movable);
	Component->SetStaticMesh(Mesh);
	Component->SetSimulatePhysics(true);

	return Actor;
}

void UPsydekick_3D::SetMeshComponentTexture(const UObject* WorldContextObject, UMeshComponent* Component, UTexture2D* Texture)
{
	FStringAssetReference assetRef("/Psydekick/Visuals/2D/GenericTextureMaterial.GenericTextureMaterial");
	UMaterial* TextureMaterial = Cast<UMaterial>(assetRef.TryLoad());

	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(TextureMaterial, Component);
	Material->SetTextureParameterValue(TEXT("Texture"), Texture);

	Component->SetMaterial(0, Material);
}

void UPsydekick_3D::SetActorTexture(const UObject* WorldContextObject, AActor* Actor, UTexture2D* Texture)
{	
	TArray<UMeshComponent*> MeshComponents;
	Actor->GetComponents<UMeshComponent>(MeshComponents, true);
	if (MeshComponents.Num() < 1) {
		UE_LOG(LogPsydekick, Error, TEXT("Cannot set texture on actor which has no mesh components"));
		return;
	}

	UPsydekick_3D::SetMeshComponentTexture(WorldContextObject, MeshComponents[0], Texture);
}

void UPsydekick_3D::MoveInDirection(const UObject* WorldContextObject, FVector Direction)
{
	APawn* Pawn = WorldContextObject->GetWorld()->GetFirstPlayerController()->GetPawn();
	UActorMovementController* MovementController = Pawn->FindComponentByClass<UActorMovementController>();
	if (MovementController == nullptr) {
		UE_LOG(LogPsydekick, Log, TEXT("Adding MovementController to Pawn"));
		MovementController = NewObject<UActorMovementController>(Pawn);
		Pawn->AddOwnedComponent(MovementController);
		MovementController->RegisterComponent();
	}
	MovementController->MoveInDirection(Direction);
}

void UPsydekick_3D::Stop(const UObject* WorldContextObject)
{
	APawn* Pawn = WorldContextObject->GetWorld()->GetFirstPlayerController()->GetPawn();
	UActorMovementController* MovementController = Pawn->FindComponentByClass<UActorMovementController>();
	if (MovementController == nullptr) {
		UE_LOG(LogPsydekick, Log, TEXT("Adding MovementController to Pawn"));
		MovementController = NewObject<UActorMovementController>(Pawn);
		Pawn->AddOwnedComponent(MovementController);
		MovementController->RegisterComponent();
	}
	MovementController->Stop();
}

