// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPGEditor : ModuleRules
{
	public FPGEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrivatePCHHeaderFile = "Public/FPGEditor.h";

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AssetTools", "LevelEditor", "EditorStyle"});

		PublicDependencyModuleNames.AddRange(new string[] { "FPG", "Slate", "SlateCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

	}
}