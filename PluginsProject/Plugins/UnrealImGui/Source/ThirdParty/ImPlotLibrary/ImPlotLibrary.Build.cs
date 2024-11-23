using UnrealBuildTool;

public class ImPlotLibrary : ModuleRules
{
#if WITH_FORWARDED_MODULE_RULES_CTOR
	public ImPlotLibrary(ReadOnlyTargetRules Target) : base(Target)
#else
	public ImGuiLibrary(TargetInfo Target)
#endif
	{
		Type = ModuleType.External;
	}
}
