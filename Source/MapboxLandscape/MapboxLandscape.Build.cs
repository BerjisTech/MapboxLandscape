using UnrealBuildTool;

public class MapboxLandscape : ModuleRules
{
	public MapboxLandscape(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"DeveloperSettings",
			"EditorSubsystem",
			"Slate",
			"SlateCore",
			"ToolMenus",
			"LevelEditor",
			"WorkspaceMenuStructure",
			"PropertyEditor",
			"HTTP",
			"ImageWrapper",
			"Json",
			"JsonUtilities",
			"Landscape",
			"LandscapeEditor",
			"WorldPartitionEditor",
			"EditorFramework",
			"UnrealEd",
			"AssetTools",
			"AssetRegistry",
			"Foliage",
			"PhysicsCore",
			"Projects",
			"RenderCore",
			"RHI",
			"PCG",
		});
	}
}
