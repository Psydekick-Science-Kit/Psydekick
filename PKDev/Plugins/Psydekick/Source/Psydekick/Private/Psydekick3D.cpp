// Fill out your copyright notice in the Description page of Project Settings.

#include "Psydekick3D.h"
#include "Psydekick.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/World.h" 
#include "Materials/MaterialInstanceDynamic.h" 
#include "GameFramework/PlayerController.h" 

#include "ActorMovementController.h" 

AStaticMeshActor* APsydekick3D::SpawnMesh(UStaticMesh* Mesh, FVector Location, FRotator Rotation)
{
	AStaticMeshActor* Actor = GetWorld()->SpawnActor<AStaticMeshActor>(Location, Rotation);
	
	UStaticMeshComponent* Component = Actor->GetStaticMeshComponent();
	Component->SetMobility(EComponentMobility::Movable);
	Component->SetStaticMesh(Mesh);
	Component->SetSimulatePhysics(true);

	return Actor;
}

void APsydekick3D::SetMeshComponentTexture(UMeshComponent* Component, UTexture2D* Texture)
{
	FStringAssetReference assetRef("/Psydekick/Visuals/2D/GenericTextureMaterial.GenericTextureMaterial");
	UMaterial* TextureMaterial = Cast<UMaterial>(assetRef.TryLoad());

	UMaterialInstanceDynamic* Material = UMaterialInstanceDynamic::Create(TextureMaterial, Component);
	Material->SetTextureParameterValue(TEXT("Texture"), Texture);

	Component->SetMaterial(0, Material);
}

void APsydekick3D::SetActorTexture(AActor* Actor, UTexture2D* Texture)
{	
	TArray<UMeshComponent*> MeshComponents;
	Actor->GetComponents<UMeshComponent>(MeshComponents, true);
	if (MeshComponents.Num() < 1) {
		UE_LOG(LogPsydekick, Error, TEXT("Cannot set texture on actor which has no mesh components"));
		return;
	}

	APsydekick3D::SetMeshComponentTexture(MeshComponents[0], Texture);
}

void APsydekick3D::MoveInDirection(FVector Direction)
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	UActorMovementController* MovementController = Pawn->FindComponentByClass<UActorMovementController>();
	if (MovementController == nullptr) {
		UE_LOG(LogPsydekick, Log, TEXT("Adding MovementController to Pawn"));
		MovementController = NewObject<UActorMovementController>(Pawn);
		Pawn->AddOwnedComponent(MovementController);
		MovementController->RegisterComponent();
	}
	MovementController->MoveInDirection(Direction);
}

void APsydekick3D::Stop()
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	UActorMovementController* MovementController = Pawn->FindComponentByClass<UActorMovementController>();
	if (MovementController == nullptr) {
		UE_LOG(LogPsydekick, Log, TEXT("Adding MovementController to Pawn"));
		MovementController = NewObject<UActorMovementController>(Pawn);
		Pawn->AddOwnedComponent(MovementController);
		MovementController->RegisterComponent();
	}
	MovementController->Stop();
}

void APsydekick3D::SetMeshComponentColor(UMeshComponent* Component, FLinearColor BaseColor)
{	
	UE_LOG(LogPsydekick, Log, TEXT("Setting component color..."));
	FStringAssetReference assetRef("/Psydekick/Visuals/2D/GenericColorMaterial.GenericColorMaterial");
	UMaterial* Material = Cast<UMaterial>(assetRef.TryLoad());
	
	UMaterialInstanceDynamic* MaterialInstance = UMaterialInstanceDynamic::Create(Material, Component);
	MaterialInstance->SetVectorParameterValue(TEXT("BaseColor"), BaseColor);

	Component->SetMaterial(0, MaterialInstance);
}