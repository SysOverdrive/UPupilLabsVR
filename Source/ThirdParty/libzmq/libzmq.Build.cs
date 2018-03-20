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
            string libPath = Path.Combine(ModuleDirectory);
         


            PublicLibraryPaths.Add(libPath);
            PublicAdditionalLibraries.Add("libzmq.lib");

            //Add header file
            PublicIncludePaths.Add(libPath);
         //    if (true) { throw new BuildException("Error Tudor " + libPath); }

            //Add DLL File
            PublicDelayLoadDLLs.Add("libzmq.dll");


        }
    }
}
