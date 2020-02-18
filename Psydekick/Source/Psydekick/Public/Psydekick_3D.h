// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/StaticMesh.h" 

#include "Psydekick_3D.generated.h"

UCLASS()
class PSYDEKICK_API UPsydekick_3D : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	//static UMaterialInterface TextureMaterial;

	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static AStaticMeshActor* SpawnMesh(const UObject* WorldContextObject, UStaticMesh* Mesh, FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void SetMeshComponentTexture(const UObject* WorldContextObject, UMeshComponent* Component, UTexture2D* Texture);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void SetActorTexture(const UObject* WorldContextObject, AActor* Actor, UTexture2D* Texture);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void MoveInDirection(const UObject* WorldContextObject, FVector Direction);

	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void Stop(const UObject* WorldContextObject);
};