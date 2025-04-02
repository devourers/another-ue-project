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
                "disco_elysium_ripoff"
            });
        PrivateDependencyModuleNames.AddRange(
            new string[] 
            {
                "UnrealEd"
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