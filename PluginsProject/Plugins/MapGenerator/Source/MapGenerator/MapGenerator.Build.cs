// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MapGenerator : ModuleRules
{
	public MapGenerator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				System.IO.Path.Combine(ModuleDirectory,"Public/Map2DProperty"),
				System.IO.Path.Combine(ModuleDirectory,"Public/Division"),
				System.IO.Path.Combine(ModuleDirectory,"Public/Sampler"),
				System.IO.Path.Combine(ModuleDirectory,"Public/Connection"),
			}
			) ;
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				System.IO.Path.Combine(ModuleDirectory,"Private/Map2DProperty"),
				System.IO.Path.Combine(ModuleDirectory,"Private/Division"),
				System.IO.Path.Combine(ModuleDirectory,"Private/Sampler"),
				System.IO.Path.Combine(ModuleDirectory,"Private/Connection")
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"RandomGenerator",
				"VoronoiDiagramModule"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"VoronoiDiagramModule"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
