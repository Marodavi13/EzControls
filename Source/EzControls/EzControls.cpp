// Copyright Epic Games, Inc. All Rights Reserved.

#include "EzControls.h"

#define LOCTEXT_NAMESPACE "FEzControlsModule"

void FEzControlsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FEzControlsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEzControlsModule, EzControls)

DEFINE_LOG_CATEGORY(LogEzControls);
