// Copyright 2023 MrRobin. All Rights Reserved.

using UnrealBuildTool;

public class CommonTime : ModuleRules
{
	public CommonTime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
        });

        PublicDependencyModuleNames.AddRange(new string[] 
        {
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "DeveloperSettings",
            "UnrealEd",
            "PropertyEditor",
            "ClassViewer",
            "InputCore",
            "BlueprintGraph",
        });
    }
}
