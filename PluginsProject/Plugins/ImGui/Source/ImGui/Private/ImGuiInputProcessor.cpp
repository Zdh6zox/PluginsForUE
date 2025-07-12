// Fill out your copyright notice in the Description page of Project Settings.


#include "ImGuiInputProcessor.h"

FImGuiInputProcessor::FImGuiInputProcessor(SImGuiOverlay* InOwner)
{
	Owner = InOwner;
	
	FSlateApplication::Get().OnApplicationActivationStateChanged().AddRaw(this, &FImGuiInputProcessor::OnApplicationActivationChanged);
}

FImGuiInputProcessor::~FImGuiInputProcessor()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().OnApplicationActivationStateChanged().RemoveAll(this);
	}
}

void FImGuiInputProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> SlateCursor)
{
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	const bool bHasGamepad = (IO.BackendFlags & ImGuiBackendFlags_HasGamepad);
	if (bHasGamepad != SlateApp.IsGamepadAttached())
	{
		IO.BackendFlags ^= ImGuiBackendFlags_HasGamepad;
	}
	
	if (IO.WantSetMousePos)
	{
		FVector2f Position = IO.MousePos;
		if (!(IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable))
		{
			// Mouse position for single viewport mode is in client space
			Position += Owner->GetTickSpaceGeometry().AbsolutePosition;
		}
	
		SlateCursor->SetPosition(Position.X, Position.Y);
	}
	
	if (IO.WantTextInput && !Owner->HasKeyboardFocus())
	{
		// No HandleKeyCharEvent so punt focus to the widget for it to receive OnKeyChar events
		SlateApp.SetKeyboardFocus(Owner->AsShared());
	}
}

bool FImGuiInputProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& Event)
{
	if (!ShouldHandleEvent(SlateApp, Event))
	{
		return false;
	}
	
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	IO.AddKeyEvent(ImGui::ConvertKey(Event.GetKey()), true);
	
	const FModifierKeysState& ModifierKeys = Event.GetModifierKeys();
	IO.AddKeyEvent(ImGuiMod_Ctrl, ModifierKeys.IsControlDown());
	IO.AddKeyEvent(ImGuiMod_Shift, ModifierKeys.IsShiftDown());
	IO.AddKeyEvent(ImGuiMod_Alt, ModifierKeys.IsAltDown());
	IO.AddKeyEvent(ImGuiMod_Super, ModifierKeys.IsCommandDown());
	
	return IO.WantCaptureKeyboard;
}

bool FImGuiInputProcessor::HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& Event)
{
	if (!ShouldHandleEvent(SlateApp, Event))
	{
		return false;
	}
	
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	IO.AddKeyEvent(ImGui::ConvertKey(Event.GetKey()), false);
	
	const FModifierKeysState& ModifierKeys = Event.GetModifierKeys();
	IO.AddKeyEvent(ImGuiMod_Ctrl, ModifierKeys.IsControlDown());
	IO.AddKeyEvent(ImGuiMod_Shift, ModifierKeys.IsShiftDown());
	IO.AddKeyEvent(ImGuiMod_Alt, ModifierKeys.IsAltDown());
	IO.AddKeyEvent(ImGuiMod_Super, ModifierKeys.IsCommandDown());
	
	return IO.WantCaptureKeyboard;
}

bool FImGuiInputProcessor::HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& Event)
{
	if (!ShouldHandleEvent(SlateApp, Event))
	{
		return false;
	}
	
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	const float Value = Event.GetAnalogValue();
	IO.AddKeyAnalogEvent(ImGui::ConvertKey(Event.GetKey()), FMath::Abs(Value) > 0.1f, Value);
	
	return IO.WantCaptureKeyboard;
}

bool FImGuiInputProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& Event)
{
	if (!ShouldHandleEvent(SlateApp, Event))
	{
		return false;
	}
	
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	if (SlateApp.HasAnyMouseCaptor())
	{
		IO.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
		return false;
	}
	
	FVector2f Position = Event.GetScreenSpacePosition();
	if (!(IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable))
	{
		// Mouse position for single viewport mode is in client space
		Position -= Owner->GetTickSpaceGeometry().AbsolutePosition;
	}
	
	IO.AddMousePosEvent(Position.X, Position.Y);
	
	return IO.WantCaptureMouse;
}

bool FImGuiInputProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& Event)
{
	if (!ShouldHandleEvent(SlateApp, Event))
	{
		return false;
	}
	
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	const FKey Button = Event.GetEffectingButton();
	if (Button == EKeys::LeftMouseButton)
	{
		IO.AddMouseButtonEvent(ImGuiMouseButton_Left, true);
	}
	else if (Button == EKeys::RightMouseButton)
	{
		IO.AddMouseButtonEvent(ImGuiMouseButton_Right, true);
	}
	else if (Button == EKeys::MiddleMouseButton)
	{
		IO.AddMouseButtonEvent(ImGuiMouseButton_Middle, true);
	}
	
	return IO.WantCaptureMouse;
}

bool FImGuiInputProcessor::HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& Event)
{
	if (!ShouldHandleEvent(SlateApp, Event))
	{
		return false;
	}
	
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	const FKey Button = Event.GetEffectingButton();
	if (Button == EKeys::LeftMouseButton)
	{
		IO.AddMouseButtonEvent(ImGuiMouseButton_Left, false);
	}
	else if (Button == EKeys::RightMouseButton)
	{
		IO.AddMouseButtonEvent(ImGuiMouseButton_Right, false);
	}
	else if (Button == EKeys::MiddleMouseButton)
	{
		IO.AddMouseButtonEvent(ImGuiMouseButton_Middle, false);
	}
	
	return false;
}

bool FImGuiInputProcessor::HandleMouseButtonDoubleClickEvent(FSlateApplication& SlateApp, const FPointerEvent& Event)
{
	// Treat as mouse down, ImGui handles double click internally
	return HandleMouseButtonDownEvent(SlateApp, Event);
}

bool FImGuiInputProcessor::HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& Event,
	const FPointerEvent* GestureEvent)
{
	if (!ShouldHandleEvent(SlateApp, Event))
	{
		return false;
	}
	
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	IO.AddMouseWheelEvent(0.0f, Event.GetWheelDelta());
	
	return IO.WantCaptureMouse;
}

void FImGuiInputProcessor::OnApplicationActivationChanged(bool bIsActive) const
{
	ImGui::FScopedContext ScopedContext(Owner->GetContext());
	
	ImGuiIO& IO = ImGui::GetIO();
	
	IO.AddFocusEvent(bIsActive);
}

bool FImGuiInputProcessor::ShouldHandleEvent(FSlateApplication& SlateApp, const FInputEvent& Event) const
{
#if WITH_EDITORONLY_DATA
	if (GIntraFrameDebuggingGameThread)
	{
		// Discard input events when the game thread is paused for debugging
		return false;
	}
#endif

	if (SlateApp.GetActiveModalWindow())
	{
		return false;
	}

	if (TSharedPtr<SWindow> Window = SlateApp.GetActiveTopLevelWindow())
	{
		if (GEngine && GEngine->GameViewport)
		{
			if (Window == GEngine->GameViewport.Get()->GetWindow())
			{
				return true;
			}
		}

		if (Window->GetTag() == "ImGuiWindow")
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	
	return false;
}
