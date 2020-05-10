// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"

#include "Psydekick3D.generated.h"

UCLASS()
class PSYDEKICK_API APsydekick3D : public AActor
{
	GENERATED_BODY()
	
public:
	AStaticMeshActor* SpawnMesh(UStaticMesh* Mesh, FVector Location, FRotator Rotation);
	void SetMeshComponentTexture(UMeshComponent* Component, UTexture2D* Texture);
	void SetMeshComponentColor(UMeshComponent* Component, FLinearColor Color);
	void SetActorTexture(AActor* Actor, UTexture2D* Texture);
	void MoveInDirection(FVector Direction);
	void Stop();
};
