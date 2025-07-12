#pragma once

#ifndef WITH_IMGUI
#define WITH_IMGUI !UE_BUILD_SHIPPING
#endif

class FImGuiMainMenuWindow;
class FImGuiManager;

class FImGuiManager
{
public:
	static FImGuiManager* GetInstance();
	void Tick();
	void OnGameBegin();
	void OnGameEnd();
	void RegisterMainMenuWindow(const FString& MenuPath, const TFunction<FImGuiMainMenuWindow*()>& CreateWindowFunc);

private:
	void UpdateMainMenuVisibility();
	void UpdateInput();
	void DrawMainMenu();
	
	bool bIsMainMenuDisplaying = false;
	bool bIsShowImGuiDemo = false;
	int32 LastFrameNumber = 0;
	TMap<FString, TSharedPtr<FImGuiMainMenuWindow>> MainMenuWindows;
};