// Copyright Epic Games, Inc. All Rights Reserved.

#include "PluginsProject.h"

#include "ImGuiModule.h"
#include "ImGuiWindowRegistrarImpl.h"
#include "Modules/ModuleManager.h"

void FPluginsProjectModule::StartupModule()
{
	// if (!FModuleManager::Get().IsModuleLoaded("ImGui"))
	// {
	// 	FModuleManager::Get().LoadModule("ImGui");
	// 	FModuleManager::LoadModuleChecked<FImGuiModule>
	// 	
	// }
	FModuleManager::LoadModuleChecked<FImGuiModule>("ImGui").AddWindowRegistrar(new FImGuiWindowRegistrarImpl());
}

IMPLEMENT_PRIMARY_GAME_MODULE( FPluginsProjectModule, PluginsProject, "PluginsProject" );
