// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UPupilLabsVR.h"
#include "Core.h"
#include "ModuleManager.h"
#include "IPluginManager.h"


#define LOCTEXT_NAMESPACE "FUPupilLabsVRModule"

	

void FUPupilLabsVRModule::StartupModule()
{	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("UPupilLabsVR")->GetBaseDir();
	
	// Add on the relative location of the third party dll and load it
#if PLATFORM_WINDOWS
	DLLPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/libzmq/Win64/libzmq.dll"));
	LibZmqDLLHandle = !DLLPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*DLLPath) : nullptr;
#endif 

	if (LibZmqDLLHandle)
	{
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("LibzmqLibraryError", "Failed to load libzmq third party library"));
	}
}

void FUPupilLabsVRModule::ShutdownModule()
{
	FPlatformProcess::FreeDllHandle(LibZmqDLLHandle);
	LibZmqDLLHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUPupilLabsVRModule, UPupilLabsVR)


/*
#if PLATFORM_WINDOWS
LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/UPupilLabsVRLibrary/Win64/ExampleLibrary.dll"));
LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/UPupilLabsVRLibrary/Win64/zmqlib.dll"));
*/