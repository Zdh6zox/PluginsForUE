#pragma once

class IMGUI_API FImGuiWindow
{
public:
	virtual ~FImGuiWindow() {}
	virtual FString GetWindowName() const = 0;
	virtual void DrawWindow() const = 0;
	bool IsDisplaying() const { return bIsDisplaying; }
	void ToggleWindowVisibility() { bIsDisplaying = !bIsDisplaying; }

private:
	bool bIsDisplaying = false;
};
