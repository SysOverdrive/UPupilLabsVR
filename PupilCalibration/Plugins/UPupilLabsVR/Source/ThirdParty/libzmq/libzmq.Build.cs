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
            PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "Libraries"));
            PublicAdditionalLibraries.Add("libzmq.lib");

            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Includes"));
            //    if (true) { throw new BuildException("Error Tudor " + libPath); }
           //Add DLL File
            PublicDelayLoadDLLs.Add("libzmq.dll");
        }
    }
}
