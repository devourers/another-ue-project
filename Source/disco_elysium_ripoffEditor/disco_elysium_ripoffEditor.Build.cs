using UnrealBuildTool;

public class disco_elysium_ripoffEditor : ModuleRules
{
	public disco_elysium_ripoffEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
        PublicIncludePaths.AddRange(
            new string[]
            {
                "disco_elysium_ripoffEditor/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[] 
            {
                "disco_elysium_ripoffEditor/Private"
            });

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "CoreUObject", 
                "Engine",
                "UMG",
                "disco_elysium_ripoff"
            });
        PrivateDependencyModuleNames.AddRange(
            new string[] 
            {
                "PythonScriptPlugin",
                "UMGEditor",
                "LevelEditor",
                "EditorFramework",
                "EditorSubsystem",
                "Blutility",
                "EditorScriptingUtilities",
                "UnrealEd",
                "Slate",
                "SlateCore"
            });

        PrivateIncludePathModuleNames.AddRange(
            new string[]
            {
            });

        DynamicallyLoadedModuleNames.AddRange(
            new string[] 
            {
            });
	}
}