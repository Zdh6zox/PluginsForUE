// 


#include "TestMainMenuWindow.h"

#include "imgui.h"

FString FTestMainMenuWindow::GetWindowName() const
{
	return FString("Test Main Menu Window");
}

void FTestMainMenuWindow::DrawWindow() const
{
	if (!ImGui::Begin(reinterpret_cast<const char*>(StringCast<UTF8CHAR>(*GetWindowName()).Get())))
	{
		ImGui::End();
		return;
	}

	ImGui::Text("Test Main Menu Window");
	ImGui::End();
}

FTestMainMenuWindow* FTestMainMenuWindow::Create()
{
	return new FTestMainMenuWindow();
}

FString FTestMainMenuWindow::GetMainMenuPath()
{
	return FString("Test Main/Test");
}

FString FAnotherTestMainMenuWindow::GetWindowName() const
{
	return FString("Another Test Main Menu Window");
}

void FAnotherTestMainMenuWindow::DrawWindow() const
{
	if (!ImGui::Begin(reinterpret_cast<const char*>(StringCast<UTF8CHAR>(*GetWindowName()).Get())))
	{
		ImGui::End();
		return;
	}

	ImGui::Button("Test Button");
	ImGui::End();
}

FAnotherTestMainMenuWindow* FAnotherTestMainMenuWindow::Create()
{
	return new FAnotherTestMainMenuWindow();
}

FString FAnotherTestMainMenuWindow::GetMainMenuPath()
{
	return FString("Test Main/Another Test");
}

