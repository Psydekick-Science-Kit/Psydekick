// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Psydekick.h"

#define LOCTEXT_NAMESPACE "FPsydekickModule"

DEFINE_LOG_CATEGORY(LogPsydekick)

void FPsydekickModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogPsydekick, Log, TEXT("Psydekick compiled %s at %s"), TEXT(__DATE__), TEXT(__TIME__));
}

void FPsydekickModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPsydekickModule, Psydekick)
