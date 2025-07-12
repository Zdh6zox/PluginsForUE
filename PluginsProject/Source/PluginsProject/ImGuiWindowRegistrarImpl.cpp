// 


#include "ImGuiWindowRegistrarImpl.h"

#include "TestMainMenuWindow.h"

FImGuiWindowRegistrarImpl::FImGuiWindowRegistrarImpl()
{
	MainWindowRegistryMap.Add(FTestMainMenuWindow::GetMainMenuPath(), FTestMainMenuWindow::Create);
	MainWindowRegistryMap.Add(FAnotherTestMainMenuWindow::GetMainMenuPath(), FAnotherTestMainMenuWindow::Create);
}
