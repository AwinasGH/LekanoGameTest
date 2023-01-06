// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LekanoTestProject : ModuleRules
{
	public LekanoTestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"UMG",
			"Slate",
			"SlateCore",
			"OnlineSubsystem",
			"OnlineSubsystemUtils"
		});
		
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
	}
}
