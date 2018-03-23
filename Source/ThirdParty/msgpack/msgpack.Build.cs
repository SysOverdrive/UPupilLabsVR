// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;


public class msgpack : ModuleRules
{
	public msgpack(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{  
            PublicLibraryPaths.Add(Path.Combine(ModuleDirectory, "Libraries"));
            PublicAdditionalLibraries.Add("msgpackc.lib");

            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Includes"));
            //    if (true) { throw new BuildException("Error Tudor " + libPath); }
           //Add DLL File
            PublicDelayLoadDLLs.Add("msgpackc.dll");
        }
    }
}
