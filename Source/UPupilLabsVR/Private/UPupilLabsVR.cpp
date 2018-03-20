// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UPupilLabsVR.h"
#include "Core.h"
#include "ModuleManager.h"


#define LOCTEXT_NAMESPACE "FUPupilLabsVRModule"

void FUPupilLabsVRModule::StartupModule()
{
	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("UPupilLabsVR")->GetBaseDir();
	
	// Add on the relative location of the third party dll and load it
#if PLATFORM_WINDOWS
	DLLPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/libzmq/X64/Release/libzmq.dll"));
#endif 
	LibZmqDLLHandle = !DLLPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*DLLPath):nullptr;
}

void FUPupilLabsVRModule::ShutdownModule()
{
	FPlatformProcess::FreeDllHandle(LibZmqDLLHandle);
	LibZmqDLLHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUPupilLabsVRModule, UPupilLabsVR)
