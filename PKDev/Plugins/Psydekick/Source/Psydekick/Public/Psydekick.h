// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPsydekick, Log, All);

class FPsydekickModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

/**
 *  \defgroup pkcpp Psydekick C++ API
 *  %Psydekick C++ API
 *  @{
 *      \defgroup pk2d 2D
 *      Interfacing with the screen
 *
 *      \defgroup pk3d 3D
 *      Interfacing with objects in the map
 *
 *      \defgroup pkdata Data
 *      Data processing tools
 *
 *      \defgroup pkflow Flow
 *      Classes/functions for program flow control
 *
 *  @}
 *
 *  \defgroup pk Psydekick Blueprints Library
 *  %Psydekick Blueprints Library
 *  @{
 *      \defgroup pk2dbp 2D
 *      Interfacing with the screen
 *
 *      \defgroup pk3dbp 3D
 *      Interfacing with objects in the map
 *
 *      \defgroup pkdatabp Data
 *      Data processing tools
 *
 *      \defgroup pkflowbp Flow
 *      Classes/functions for program flow control
 *
 *  @}
 */
