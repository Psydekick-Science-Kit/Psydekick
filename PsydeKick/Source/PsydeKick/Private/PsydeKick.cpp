// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PsydeKick.h"

#define LOCTEXT_NAMESPACE "FPsydeKickModule"

DEFINE_LOG_CATEGORY(LogPsydeKick)

void FPsydeKickModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogPsydeKick, Log, TEXT("Psydekick compiled %s at %s"), TEXT(__DATE__), TEXT(__TIME__));
}

void FPsydeKickModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPsydeKickModule, PsydeKick)