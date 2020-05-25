// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/StaticMesh.h"

#include "3D/Psydekick3D.h"

#include "Psydekick3D_BPLibrary.generated.h"


/** @ingroup pk3dbp
 *
 */
UCLASS()
class PSYDEKICK_API UPsydekick3D_BPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	static APsydekick3D* PK3DActor;

public:
	static APsydekick3D* GetPK3DActor(const UObject* WorldContextObject);

	/**
	 * @brief Spawn a static mesh actor
	 *
	 * @param Mesh The mesh to spawn
	 * @param Location World location to spawn at
	 * @param Rotation World rotation to spawn with
	 * @return AStaticMeshActor*
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static AStaticMeshActor* SpawnMesh(const UObject* WorldContextObject, UStaticMesh* Mesh, FVector Location, FRotator Rotation);

	/**
	 * @brief Apply a texture to a mesh component
	 *
	 * @param Component The component to receive the texture
	 * @param Texture The texture to apply
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void SetMeshComponentTexture(const UObject* WorldContextObject, UMeshComponent* Component, UTexture2D* Texture);

	/**
	 * @brief Apply a texture to an actor's first MeshComponent
	 *
	 * @param Actor The actor whose MeshComponent will receive the texture
	 * @param Texture The texture to apply
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void SetActorTexture(const UObject* WorldContextObject, AActor* Actor, UTexture2D* Texture);

	/**
	 * @brief Set the player's pawn in motion
	 *
	 * @param Direction The direction to move
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void MoveInDirection(const UObject* WorldContextObject, FVector Direction);

	/**
	 * @brief Stop the player's pawn
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void Stop(const UObject* WorldContextObject);

	/**
	 * @brief Apply a color to a MeshComponent
	 *
	 * @param Component The component to receive the new color
	 * @param BaseColor The color to apply
	 */
	UFUNCTION(BlueprintCallable, Category = "Psydekick|3D", meta = (WorldContext = WorldContextObject))
	static void SetMeshComponentColor(const UObject* WorldContextObject, UMeshComponent* Component, FLinearColor BaseColor);
};
