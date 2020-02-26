// Fill out your copyright notice in the Description page of Project Settings.

#include "PsydekickVisuals2D_BPLibrary.h"
#include "Psydekick.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h" 

#include "Kismet/GameplayStatics.h" 

#include "PsydekickVisuals2D.h"

APsydekickVisuals2D* UPsydekickVisuals2D_BPLibrary::PKVisuals2DActor;

APsydekickVisuals2D* UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(const UObject* WorldContextObject)
{
    UWorld* World = WorldContextObject->GetWorld();

    TArray<AActor*> Instances;
    UGameplayStatics::GetAllActorsOfClass(World, APsydekickVisuals2D::StaticClass(), Instances);

    bool NeedToSpawn = (!PKVisuals2DActor) || (Instances.Num() < 1);
    if(!NeedToSpawn)
    {
        PKVisuals2DActor = (APsydekickVisuals2D*)Instances.Last();
        NeedToSpawn = NeedToSpawn || (World != PKVisuals2DActor->GetWorld());
    }
    
    if(NeedToSpawn)
    {
        UE_LOG(LogPsydekick, Log, TEXT("Spawning new PKVisuals2DActor"));
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        PKVisuals2DActor = World->SpawnActor<APsydekickVisuals2D>(SpawnParams);
    }

    return PKVisuals2DActor;
}

void UPsydekickVisuals2D_BPLibrary::ShowText(const UObject* WorldContextObject, const FString Text)
{
    UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ShowText(Text);
}

void UPsydekickVisuals2D_BPLibrary::ClearScreen(const UObject* WorldContextObject)
{
    UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ClearScreen();
}

void UPsydekickVisuals2D_BPLibrary::ShowImage(const UObject* WorldContextObject, UTexture* Image)
{
    UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->ShowImage(Image);
}

void UPsydekickVisuals2D_BPLibrary::GetChoice(const UObject* WorldContextObject, const FString Prompt, const TArray<FString> Options, const FChoiceMade &ChoiceMade)
{
    UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->GetChoice(Prompt, Options, ChoiceMade);
}

void UPsydekickVisuals2D_BPLibrary::SetUIMode(const UObject* WorldContextObject)
{
    UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->SetUIMode();
}

void UPsydekickVisuals2D_BPLibrary::SetGameOnlyMode(const UObject* WorldContextObject)
{
    UPsydekickVisuals2D_BPLibrary::GetPKVisuals2DActor(WorldContextObject)->SetGameOnlyMode();
}
