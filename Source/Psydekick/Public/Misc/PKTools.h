// (c) 2021 Dominic Canare <dom@dominiccanare.com>

#pragma once

#include "CoreMinimal.h"

class PSYDEKICK_API PKTools
{
public:
	PKTools();
	~PKTools();

	static UObject* LoadAssetFromContent(FString Path);
	static UClass* GetBlueprintClass(FString BPAssetPath);
};


