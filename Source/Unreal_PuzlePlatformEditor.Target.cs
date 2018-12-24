// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Unreal_PuzlePlatformEditorTarget : TargetRules
{
	public Unreal_PuzlePlatformEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("Unreal_PuzlePlatform");
	}
}
