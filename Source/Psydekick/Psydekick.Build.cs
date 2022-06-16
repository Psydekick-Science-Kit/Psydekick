// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class Psydekick : ModuleRules
{
	protected virtual string SDL2Version { get { return "SDL-gui-backend"; } }
	protected virtual string IncRootDirectory { get { return Target.UEThirdPartySourceDirectory; } }
	protected virtual string LibRootDirectory { get { return Target.UEThirdPartySourceDirectory; } }

	protected virtual string SDL2IncPath { get { return Path.Combine(IncRootDirectory, "SDL2", SDL2Version, "include"); } }
	protected virtual string SDL2LibPath { get { return Path.Combine(LibRootDirectory, "SDL2", SDL2Version, "lib"); } }

	public Psydekick(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDefinitions.Add("SDL_WITH_EPIC_EXTENSIONS=1");
		PublicIncludePaths.Add(SDL2IncPath);

		PublicIncludePaths.AddRange(
			new string[] {
				"ThirdParty/SDL2/SDL-gui-backend/include/"
			}
		);

		if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
		{
		if (Target.Configuration == UnrealTargetConfiguration.Debug)
			{
				// Debug version should be built with -fPIC and usable in all targets
				PublicAdditionalLibraries.Add(Path.Combine(SDL2LibPath, "Linux", Target.Architecture, "libSDL2_fPIC_Debug.a"));
			}
			else if (Target.LinkType == TargetLinkType.Monolithic)
			{
				PublicAdditionalLibraries.Add(Path.Combine(SDL2LibPath, "Linux", Target.Architecture, "libSDL2.a"));
			}
			else
			{
				PublicAdditionalLibraries.Add(Path.Combine(SDL2LibPath, "Linux", Target.Architecture, "libSDL2_fPIC.a"));
			}
		}
		else if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(SDL2LibPath, "Win64", "SDL2.lib"));

			RuntimeDependencies.Add(Path.Combine("$(EngineDir)", "Binaries", "ThirdParty", "SDL2", "Win64/SDL2.dll"));
			PublicDelayLoadDLLs.Add("SDL2.dll");
		}

		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UMG",
				"InputCore",
				"MediaAssets",
				"AudioMixer",
				"PhysXVehicles",
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
