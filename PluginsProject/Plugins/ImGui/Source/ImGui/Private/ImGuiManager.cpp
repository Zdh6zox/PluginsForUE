#include "ImGuiManager.h"

#include "imgui.h"
#include "ImGuiConfig.h"
#include "ImGuiMainMenuWindow.h"
#include "ImGuiModule.h"
#include "ImGuiWindowRegistrar.h"
#include "Kismet/GameplayStatics.h"

FImGuiManager* FImGuiManager::GetInstance()
{
	if (!FModuleManager::Get().IsModuleLoaded("ImGui"))
	{
		return nullptr;
	}
	
	return FImGuiModule::Get().GetImGuiManager();
}

void FImGuiManager::Tick()
{
	SCOPED_NAMED_EVENT(FImGuiManager_Tick, FColor::Blue);

	if (LastFrameNumber < GFrameCounter)
	{
		LastFrameNumber = GFrameCounter;
		ImGui::FScopedContext Context;
		if (!Context)
		{
			return;
		}
		
		UpdateMainMenuVisibility();

		DrawMainMenu();
	}
}

void FImGuiManager::OnGameBegin()
{
	for (auto ConstRegistrarIter = FImGuiModule::Get().GetWindowRegistrarConstIterator(); ConstRegistrarIter; ++ConstRegistrarIter)
	{
		for (auto ConstRegisteredWindowIter = ConstRegistrarIter->Get()->GetWindowRegistryMap().CreateConstIterator(); ConstRegisteredWindowIter; ++ConstRegisteredWindowIter)
		{
			RegisterMainMenuWindow(ConstRegisteredWindowIter.Key(), ConstRegisteredWindowIter.Value());
		}
	}
}

void FImGuiManager::OnGameEnd()
{
	bIsMainMenuDisplaying = false;
	bIsShowImGuiDemo = false;
	MainMenuWindows.Empty();
}

void FImGuiManager::RegisterMainMenuWindow(const FString& MenuPath, const TFunction<FImGuiMainMenuWindow*()>& CreateWindowFunc)
{
	if (MainMenuWindows.Contains(MenuPath))
	{
		return;
	}

	TSharedPtr<FImGuiMainMenuWindow> CreatedWindow = MakeShareable<FImGuiMainMenuWindow>(CreateWindowFunc());
	MainMenuWindows.Add(MenuPath, CreatedWindow);
}

void FImGuiManager::UpdateMainMenuVisibility()
{
	if (ImGui::IsKeyPressed(ImGuiKey_Slash, false))
	{
		bIsMainMenuDisplaying = !bIsMainMenuDisplaying;
	}

	UWorld* CurrentWorld = GEngine->GetCurrentPlayWorld();
	if (CurrentWorld == nullptr)
	{
		return;
	}

	UpdateInput();
	
	if (bIsMainMenuDisplaying)
	{
		constexpr float NearlyPausingTimeDilation = 0.001f;
		UGameplayStatics::SetGlobalTimeDilation(CurrentWorld, NearlyPausingTimeDilation);
	}
	else
	{
		UGameplayStatics::SetGlobalTimeDilation(CurrentWorld, 1.0f);
	}
}

void FImGuiManager::UpdateInput()
{
	if (bIsMainMenuDisplaying)
	{
		if (GWorld)
		{
			if (APlayerController* PlayerController = GWorld->GetFirstPlayerController())
			{
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeUIOnly());
			}
		}
	}
	else
	{
		if (GWorld)
		{
			if (APlayerController* PlayerController = GWorld->GetFirstPlayerController())
			{
				if (PlayerController->IsPaused())
				{
					PlayerController->bShowMouseCursor = true;
					PlayerController->SetInputMode(FInputModeGameAndUI());
				}
				else
				{
					PlayerController->bShowMouseCursor = false;
					PlayerController->SetInputMode(FInputModeGameOnly());
				}
			}
		}

		// // Clear ImGui Window focus
		// ImGui::GetIO().AddMousePosEvent(-FLT_MIN, -FLT_MAX);
	}
}

void FImGuiManager::DrawMainMenu()
{
	if (bIsMainMenuDisplaying)
	{
		if (ImGui::BeginMainMenuBar())
		{
			for (auto ConstIter = MainMenuWindows.CreateConstIterator(); ConstIter; ++ConstIter)
			{
				FString MenuName = "";
				FString ItemName = "";
				ConstIter.Key().Split("/", &MenuName, &ItemName);
				if (ImGui::BeginMenu(TCHAR_TO_UTF8(*MenuName)))
				{
					if (ImGui::MenuItem(TCHAR_TO_UTF8(*ItemName)))
					{
						ConstIter.Value()->ToggleWindowVisibility();
					}
					ImGui::EndMenu();
				}
			}
		
			if (ImGui::BeginMenu("ImGui"))
			{
				if (ImGui::MenuItem("Demo"))
				{
					bIsShowImGuiDemo = !bIsShowImGuiDemo;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	for (auto ConstIter = MainMenuWindows.CreateConstIterator(); ConstIter; ++ConstIter)
	{
		if (ConstIter->Value->IsDisplaying())
		{
			ConstIter->Value->DrawWindow();
		}
	}
	

	if (bIsShowImGuiDemo)
	{
		ImGui::ShowDemoWindow();
	}
}
