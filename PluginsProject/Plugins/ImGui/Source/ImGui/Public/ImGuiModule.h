#pragma once

#include <Misc/EngineVersionComparison.h>
#include <Modules/ModuleManager.h>
#include "ImGuiManager.h"

class FImGuiWindowRegistrar;
class FImGuiContext;
class SWindow;
class UGameViewportClient;
class FImGuiManager;

class IMGUI_API FImGuiModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/// Returns this module's instance, loading it on demand if needed
	/// @note Beware of calling this during the shutdown phase as the module might have been unloaded already
	static FImGuiModule& Get();

	FImGuiManager* GetImGuiManager() const;
	void AddWindowRegistrar(FImGuiWindowRegistrar* InRegistrar);
	TArray<TSharedPtr<FImGuiWindowRegistrar>>::TConstIterator GetWindowRegistrarConstIterator() const;

	/// Finds or creates an ImGui context for an editor or game session
	/// @param PieSessionId Optional target Play-in-Editor instance, defaults to the current instance
#if UE_VERSION_OLDER_THAN(5, 5, 0)
	TSharedPtr<FImGuiContext> FindOrCreateSessionContext(const int32 PieSessionId = GPlayInEditorID);
#else
	TSharedPtr<FImGuiContext> FindOrCreateSessionContext(const int32 PieSessionId = UE::GetPlayInEditorID());
#endif

	/// Creates an ImGui context for a Slate window
	static TSharedPtr<FImGuiContext> CreateWindowContext(const TSharedRef<SWindow>& Window);

	/// Creates an ImGui context for a game viewport
	static TSharedPtr<FImGuiContext> CreateViewportContext(UGameViewportClient* GameViewport);

private:
	void OnStartPIE(bool bIsSimulating);
	void OnEndPIE(bool bIsSimulating);
	void OnViewportCreated() const;
	void OnWorldTickEnd(UWorld* World, ELevelTick TickType, float DeltaSeconds);

	TMap<int32, TSharedPtr<FImGuiContext>> SessionContexts;
	TUniquePtr<FImGuiManager> ImGuiManager;
	TArray<TSharedPtr<FImGuiWindowRegistrar>> WindowRegistrars;
};
