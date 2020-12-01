// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class PSYDEKICK_API PKTools
{
public:
	PKTools();
	~PKTools();

	static UObject* LoadAssetFromContent(FString Path);
	static UClass* GetBlueprintClass(FString BPAssetPath);
};


