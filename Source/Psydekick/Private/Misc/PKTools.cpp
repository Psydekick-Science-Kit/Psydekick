// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/PKTools.h"

#include "Engine/StreamableManager.h"


PKTools::PKTools()
{
}

PKTools::~PKTools()
{
}


UObject* PKTools::LoadAssetFromContent(FString Path)
{
	FStringAssetReference* AssetRef = new FStringAssetReference(Path);
	FStreamableManager AssetLoader;
	UObject* LoadedAsset = nullptr;

	LoadedAsset = AssetLoader.LoadSynchronous(*AssetRef);
	delete AssetRef;

	return LoadedAsset;
}

UClass* PKTools::GetBlueprintClass(FString BPAssetPath)
{
	UBlueprint* Blueprint = Cast<UBlueprint>(PKTools::LoadAssetFromContent(BPAssetPath));
	return (UClass*)Blueprint->GeneratedClass;
}
