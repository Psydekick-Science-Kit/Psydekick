// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#include "3D/Psydekick3D_BPLibrary.h"

#include "Psydekick.h"

#include "Kismet/GameplayStatics.h"

APsydekick3D* UPsydekick3D_BPLibrary::PK3DActor;

APsydekick3D* UPsydekick3D_BPLibrary::GetPK3DActor(const UObject* WorldContextObject)
{
	UWorld* World = WorldContextObject->GetWorld();

	TArray<AActor*> Instances;
	UGameplayStatics::GetAllActorsOfClass(World, APsydekick3D::StaticClass(), Instances);

	bool NeedToSpawn = (!PK3DActor) || (Instances.Num() < 1);
	if(!NeedToSpawn)
	{
		PK3DActor = (APsydekick3D*)Instances.Last();
		NeedToSpawn = NeedToSpawn || (World != PK3DActor->GetWorld());
	}

	if(NeedToSpawn)
	{
		UE_LOG(LogPsydekick, Log, TEXT("Spawning new PK3DActor"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PK3DActor = World->SpawnActor<APsydekick3D>(SpawnParams);
	}

	return PK3DActor;
}

AStaticMeshActor* UPsydekick3D_BPLibrary::SpawnMesh(const UObject* WorldContextObject, UStaticMesh* Mesh, FVector Location, FRotator Rotation)
{
	return UPsydekick3D_BPLibrary::GetPK3DActor(WorldContextObject)->SpawnMesh(Mesh, Location, Rotation);
}

void UPsydekick3D_BPLibrary::SetMeshComponentTexture(const UObject* WorldContextObject, UMeshComponent* Component, UTexture2D* Texture)
{
	UPsydekick3D_BPLibrary::GetPK3DActor(WorldContextObject)->SetMeshComponentTexture(Component, Texture);
}

void UPsydekick3D_BPLibrary::SetActorTexture(const UObject* WorldContextObject, AActor* Actor, UTexture2D* Texture)
{
	UPsydekick3D_BPLibrary::GetPK3DActor(WorldContextObject)->SetActorTexture(Actor, Texture);
}

void UPsydekick3D_BPLibrary::MoveInDirection(const UObject* WorldContextObject, FVector Direction)
{
	UPsydekick3D_BPLibrary::GetPK3DActor(WorldContextObject)->MoveInDirection(Direction);
}

void UPsydekick3D_BPLibrary::Stop(const UObject* WorldContextObject)
{
	UPsydekick3D_BPLibrary::GetPK3DActor(WorldContextObject)->Stop();
}

void UPsydekick3D_BPLibrary::SetMeshComponentColor(const UObject* WorldContextObject, UMeshComponent* Component, FLinearColor BaseColor)
{
	UPsydekick3D_BPLibrary::GetPK3DActor(WorldContextObject)->SetMeshComponentColor(Component, BaseColor);
}
