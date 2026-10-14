// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Lab06 : ModuleRules
{
	public Lab06(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Lab06",
			"Lab06/Variant_Platforming",
			"Lab06/Variant_Platforming/Animation",
			"Lab06/Variant_Combat",
			"Lab06/Variant_Combat/AI",
			"Lab06/Variant_Combat/Animation",
			"Lab06/Variant_Combat/Gameplay",
			"Lab06/Variant_Combat/Interfaces",
			"Lab06/Variant_Combat/UI",
			"Lab06/Variant_SideScrolling",
			"Lab06/Variant_SideScrolling/AI",
			"Lab06/Variant_SideScrolling/Gameplay",
			"Lab06/Variant_SideScrolling/Interfaces",
			"Lab06/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
