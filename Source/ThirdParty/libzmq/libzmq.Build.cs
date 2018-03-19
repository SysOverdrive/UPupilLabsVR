// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class libzmq : ModuleRules
{
	public libzmq(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "Libraries"));
			PublicAdditionalLibraries.Add("libzmq.lib");
            //Add header file
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Includes"));
            
        }
    }
}
