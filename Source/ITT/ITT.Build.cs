// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ITT : ModuleRules
{
	public ITT(ReadOnlyTargetRules Target) : base(Target)
	{
		// ========== PCH ========== //
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PrivatePCHHeaderFile = "ITT.h";
		// ========================= //
		
		
		// ========== Paths ========== //
		PrivateIncludePaths.Add("ITT");
		PrivateIncludePaths.Add("ITT/Utility");
		// =========================== //
		
		
		// ========== Modules ========== //
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"CommonUI", "Slate", "SlateCore", "UMG"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
		// ============================= //
	}
}
