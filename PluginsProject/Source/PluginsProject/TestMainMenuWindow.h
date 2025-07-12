// 

#pragma once

#include "CoreMinimal.h"
#include "ImGuiMainMenuWindow.h"

/**
 * 
 */
class PLUGINSPROJECT_API FTestMainMenuWindow : public FImGuiMainMenuWindow
{
public:
    virtual FString GetWindowName() const override;
    virtual void DrawWindow() const override;

	static FTestMainMenuWindow* Create();
	static FString GetMainMenuPath();
};

/**
 * 
 */
class PLUGINSPROJECT_API FAnotherTestMainMenuWindow : public FImGuiMainMenuWindow
{
public:
	virtual FString GetWindowName() const override;
	virtual void DrawWindow() const override;

	static FAnotherTestMainMenuWindow* Create();
	static FString GetMainMenuPath();
};
