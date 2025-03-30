// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class disco_elysium_ripoff : ModuleRules
{
	public disco_elysium_ripoff(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "AIModule", "NavigationSystem", "UMG"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities" });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { 
				"PythonScriptPlugin", 
				"UMGEditor", 
				"LevelEditor", 
				"EditorSubsystem", 
				"Blutility", 
				"EditorScriptingUtilities", 
				"UnrealEd" });
        }

        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
