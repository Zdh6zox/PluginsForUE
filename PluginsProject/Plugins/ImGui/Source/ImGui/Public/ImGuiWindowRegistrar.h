// 

#pragma once

#include "CoreMinimal.h"

class FImGuiMainMenuWindow;
/**
 * 
 */
class IMGUI_API FImGuiWindowRegistrar
{
public:
	virtual ~FImGuiWindowRegistrar() = default;
	const TMap<FString, TFunction<FImGuiMainMenuWindow*()>>& GetWindowRegistryMap() const { return MainWindowRegistryMap; }
protected:
    TMap<FString, TFunction<FImGuiMainMenuWindow*()>> MainWindowRegistryMap;
};
