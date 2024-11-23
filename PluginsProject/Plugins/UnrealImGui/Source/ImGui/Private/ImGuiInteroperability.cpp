// Distributed under the MIT License (MIT) (see accompanying LICENSE file)

#include "ImGuiInteroperability.h"

#include "ImGuiInputState.h"
#include "Utilities/Arrays.h"


// If TCHAR is wider than ImWchar, enable or disable validation of input character before conversions.
#define VALIDATE_INPUT_CHARACTERS 1

#if VALIDATE_INPUT_CHARACTERS
DEFINE_LOG_CATEGORY_STATIC(LogImGuiInput, Warning, All);
#endif

namespace
{
	//====================================================================================================
	// Character conversion
	//====================================================================================================

	template<typename T, std::enable_if_t<(sizeof(T) <= sizeof(ImWchar)), T>* = nullptr>
	ImWchar CastInputChar(T Char)
	{
		return static_cast<ImWchar>(Char);
	}

	template<typename T, std::enable_if_t<!(sizeof(T) <= sizeof(ImWchar)), T>* = nullptr>
	ImWchar CastInputChar(T Char)
	{
#if VALIDATE_INPUT_CHARACTERS
		// We only need a runtime validation if TCHAR is wider than ImWchar.
		// Signed and unsigned integral types with the same size as ImWchar should be safely converted. As long as the
		// char value is in that range we can safely use it, otherwise we should log an error to notify about possible
		// truncations.
		static constexpr auto MinLimit = (std::numeric_limits<std::make_signed_t<ImWchar>>::min)();
		static constexpr auto MaxLimit = (std::numeric_limits<std::make_unsigned_t<ImWchar>>::max)();
		UE_CLOG(!(Char >= MinLimit && Char <= MaxLimit), LogImGuiInput, Error,
			TEXT("TCHAR value '%c' (%#x) is out of range %d (%#x) to %u (%#x) that can be safely converted to ImWchar. ")
			TEXT("If you wish to disable this validation, please set VALIDATE_INPUT_CHARACTERS in ImGuiInputState.cpp to 0."),
			Char, Char, MinLimit, MinLimit, MaxLimit, MaxLimit);
#endif

		return static_cast<ImWchar>(Char);
	}

	//====================================================================================================
	// Copying Utilities
	//====================================================================================================

	// Copy all elements from source to destination array of the same size.
	template<typename TArray>
	void Copy(const TArray& Src, TArray& Dst)
	{
		using std::copy;
		using std::begin;
		using std::end;
		copy(begin(Src), end(Src), begin(Dst));
	}

	// Copy subrange of source array to destination array of the same size.
	template<typename TArray, typename SizeType>
	void Copy(const TArray& Src, TArray& Dst, const Utilities::TArrayIndexRange<TArray, SizeType>& Range)
	{
		using std::copy;
		using std::begin;
		copy(begin(Src) + Range.GetBegin(), begin(Src) + Range.GetEnd(), begin(Dst) + Range.GetBegin());
	}

	// Copy number of elements from the beginning of source array to the beginning of destination array of the same size.
	template<typename TArray, typename SizeType>
	void Copy(const TArray& Src, TArray& Dst, SizeType Count)
	{
		checkf(Count < Utilities::ArraySize<TArray>::value, TEXT("Number of copied elements is larger than array size."));

		using std::copy;
		using std::begin;
		copy(begin(Src), begin(Src) + Count, begin(Dst));
	}
}

namespace ImGuiInterops
{
	//====================================================================================================
	// Input Mapping
	//====================================================================================================

	// void SetUnrealKeyMap(ImGuiIO& IO)
	// {
	// 	struct FUnrealToImGuiMapping
	// 	{
	// 		FUnrealToImGuiMapping()
	// 		{

	// 		}
	//
	// 		ImGuiTypes::FKeyMap KeyMap;
	// 	};
	//
	// 	static const FUnrealToImGuiMapping Mapping;
	//
	// 	Copy(Mapping.KeyMap, IO.AddKeyEvent());
	// }

	// OLD ->
	// Simple transform mapping key codes to 0-511 range used in ImGui.
	// From what I can tell, on most supported platforms key codes should comfortably fit in that range anyway
	// but the SDL key-codes used on Linux can go way out of this range (because of the extra flag). However,
	// after this transform they should fit in the range without conflicts.
	// NOTE: Should any of the platforms have other conflicts or any trouble with inputs, this is the likely
	// candidate for change.

	// Since we are using ImGui 1.91.6, need do refactoring on input mapping!!!
	static uint32 MapKeyCode(uint32 KeyCode)
	{
		return KeyCode + ImGuiKey_NamedKey_BEGIN;
	}

	ImGuiKey MapKey(const FKey& Key)
	{
		// switch (GetKeyIndex(Key))
		// {
		// case GetKeyIndex(EKeys::Tab): return ImGuiKey_Tab;
		// case GetKeyIndex(EKeys::Left): return ImGuiKey_LeftArrow;
		// case GetKeyIndex(EKeys::Right): return ImGuiKey_RightArrow;
		// case GetKeyIndex(EKeys::Up): return ImGuiKey_UpArrow;
		// case GetKeyIndex(EKeys::Down): return ImGuiKey_DownArrow;
		// case GetKeyIndex(EKeys::PageUp): return ImGuiKey_PageUp;
		// case GetKeyIndex(EKeys::PageDown): return ImGuiKey_PageDown;
		// case GetKeyIndex(EKeys::Home): return ImGuiKey_Home;
		// case GetKeyIndex(EKeys::End): return ImGuiKey_End;
		// case GetKeyIndex(EKeys::Insert): return ImGuiKey_Insert;
		// case GetKeyIndex(EKeys::Delete): return ImGuiKey_Delete;
		// case GetKeyIndex(EKeys::BackSpace): return ImGuiKey_Backspace;
		// case GetKeyIndex(EKeys::SpaceBar): return ImGuiKey_Space;
		// case GetKeyIndex(EKeys::Enter): return ImGuiKey_Enter;
		// case GetKeyIndex(EKeys::Escape): return ImGuiKey_Escape;
		// case GetKeyIndex(EKeys::A): return ImGuiKey_A;
		// case GetKeyIndex(EKeys::C): return ImGuiKey_C;
		// case GetKeyIndex(EKeys::V): return ImGuiKey_V;
		// case GetKeyIndex(EKeys::X): return ImGuiKey_X;
		// case GetKeyIndex(EKeys::Y): return ImGuiKey_Y;
		// case GetKeyIndex(EKeys::Z): return ImGuiKey_Z;
		// default: return ImGuiKey_None;
		// }

		if (Key == EKeys::A)
		{
			return ImGuiKey_A;
		}
		else if (Key == EKeys::C)
		{
			return ImGuiKey_C;
		}

		return ImGuiKey_None;
	}

	ImGuiKey MapAxis(const FKey& Key, float Value)
	{
		// switch (Key)
		// {
		// case GetKeyIndex(EKeys::Gamepad_LeftX):
		// 	{
		// 		if (Value <= 0.f)
		// 		{
		// 			return ImGuiKey_GamepadLStickLeft;
		// 		}
		// 		return ImGuiKey_GamepadLStickRight;
		// 	}
		// case GetKeyIndex(EKeys::Gamepad_LeftY):
		// 	{
		// 		if (Value <= 0.f)
		// 		{
		// 			return ImGuiKey_GamepadLStickDown;
		// 		}
		//
		// 		return ImGuiKey_GamepadLStickUp;
		// 	}
		// 	default: return ImGuiKey_None;
		// }

		if (Key == EKeys::Gamepad_LeftX)
		{
			if (Value <= 0.f)
			{
				return ImGuiKey_GamepadLStickLeft;
			}
			return ImGuiKey_GamepadLStickRight;
		}
		else if (Key == EKeys::Gamepad_LeftY)
		{
			if (Value <= 0.f)
			{
				return ImGuiKey_GamepadLStickDown;
			}
			
			return ImGuiKey_GamepadLStickUp;
		}
		return ImGuiKey_None;
	}
	


	uint32 GetKeyIndex(const FKey& Key)
	{
		const uint32* pKeyCode = nullptr;
		const uint32* pCharCode = nullptr;

		FInputKeyManager::Get().GetCodesFromKey(Key, pKeyCode, pCharCode);

		const uint32 KeyCode =
			pKeyCode ? *pKeyCode
			: pCharCode ? *pCharCode
			: 0;

		return MapKeyCode(KeyCode);
	}

	uint32 GetKeyIndex(const FKeyEvent& KeyEvent)
	{
		return MapKeyCode(KeyEvent.GetKeyCode());
	}

	uint32 GetMouseIndex(const FKey& MouseButton)
	{
		if (MouseButton == EKeys::LeftMouseButton)
		{
			return 0;
		}
		else if (MouseButton == EKeys::MiddleMouseButton)
		{
			return 2;
		}
		else if (MouseButton == EKeys::RightMouseButton)
		{
			return 1;
		}
		else if (MouseButton == EKeys::ThumbMouseButton)
		{
			return 3;
		}
		else if (MouseButton == EKeys::ThumbMouseButton2)
		{
			return 4;
		}

		return -1;
	}

	EMouseCursor::Type ToSlateMouseCursor(ImGuiMouseCursor MouseCursor)
	{
		switch (MouseCursor)
		{
		case ImGuiMouseCursor_Arrow:
			return EMouseCursor::Default;
		case ImGuiMouseCursor_TextInput:
			return EMouseCursor::TextEditBeam;
		case ImGuiMouseCursor_ResizeAll:
			return EMouseCursor::CardinalCross;
		case ImGuiMouseCursor_ResizeNS:
			return  EMouseCursor::ResizeUpDown;
		case ImGuiMouseCursor_ResizeEW:
			return  EMouseCursor::ResizeLeftRight;
		case ImGuiMouseCursor_ResizeNESW:
			return  EMouseCursor::ResizeSouthWest;
		case ImGuiMouseCursor_ResizeNWSE:
			return  EMouseCursor::ResizeSouthEast;
		case ImGuiMouseCursor_None:
		default:
			return EMouseCursor::None;
		}
	}

	namespace
	{
		inline void UpdateKey(const FKey& Key, const FKey& KeyCondition, float& Value, bool bIsDown)
		{
			if (Key == KeyCondition)
			{
				Value = (bIsDown) ? 1.f : 0.f;
			}
		}

		inline void UpdateAxisValues(float& Axis, float& Opposite, float Value)
		{
			constexpr float AxisInputThreshold = 0.166f;

			// Filter out small values to avoid false positives (helpful in case of worn controllers).
			Axis = FMath::Max(0.f, Value - AxisInputThreshold);
			Opposite = 0.f;
		}

		inline void UpdateSymmetricAxis(const FKey& Key, const FKey& KeyCondition, float& Negative, float& Positive, float Value)
		{
			if (Key == KeyCondition)
			{
				if (Value < 0.f)
				{
					UpdateAxisValues(Negative, Positive, -Value);
				}
				else
				{
					UpdateAxisValues(Positive, Negative, Value);
				}
			}
		}
	}

	void SetGamepadNavigationKey(ImGuiTypes::FNavInputArray& NavInputs, const FKey& Key, bool bIsDown)
	{
#define MAP_KEY(KeyCondition, NavIndex) UpdateKey(Key, KeyCondition, NavInputs[NavIndex], bIsDown)

		if (Key.IsGamepadKey())
		{
			MAP_KEY(EKeys::Gamepad_FaceButton_Bottom, ImGuiKey_GamepadFaceDown);
			MAP_KEY(EKeys::Gamepad_FaceButton_Right, ImGuiKey_GamepadFaceRight);
			MAP_KEY(EKeys::Gamepad_FaceButton_Top, ImGuiKey_GamepadFaceUp);
			MAP_KEY(EKeys::Gamepad_FaceButton_Left, ImGuiKey_GamepadFaceLeft);
			MAP_KEY(EKeys::Gamepad_DPad_Left, ImGuiKey_GamepadDpadLeft);
			MAP_KEY(EKeys::Gamepad_DPad_Right, ImGuiKey_GamepadDpadRight);
			MAP_KEY(EKeys::Gamepad_DPad_Up, ImGuiKey_GamepadDpadUp);
			MAP_KEY(EKeys::Gamepad_DPad_Down, ImGuiKey_GamepadDpadDown);
			MAP_KEY(EKeys::Gamepad_LeftShoulder, ImGuiKey_GamepadL1);
			MAP_KEY(EKeys::Gamepad_RightShoulder, ImGuiKey_GamepadR1);
			MAP_KEY(EKeys::Gamepad_LeftTrigger, ImGuiKey_GamepadL2);
			MAP_KEY(EKeys::Gamepad_RightTrigger, ImGuiKey_GamepadR2);
		}

#undef MAP_KEY
	}

	void SetGamepadNavigationAxis(ImGuiTypes::FNavInputArray& NavInputs, const FKey& Key, float Value)
	{
#define MAP_SYMMETRIC_AXIS(KeyCondition, NegNavIndex, PosNavIndex) UpdateSymmetricAxis(Key, KeyCondition, NavInputs[NegNavIndex], NavInputs[PosNavIndex], Value)

		if (Key.IsGamepadKey())
		{
			MAP_SYMMETRIC_AXIS(EKeys::Gamepad_LeftX, ImGuiKey_GamepadLStickLeft, ImGuiKey_GamepadLStickRight);
			MAP_SYMMETRIC_AXIS(EKeys::Gamepad_LeftY, ImGuiKey_GamepadLStickUp, ImGuiKey_GamepadLStickDown);
		}

#undef MAP_SYMMETRIC_AXIS

		
	}

	//====================================================================================================
	// Input State Copying
	//====================================================================================================

	template<typename TFlags, typename TFlag>
	static inline constexpr void SetFlag(TFlags& Flags, TFlag Flag, bool bSet)
	{
		Flags = bSet ? Flags | Flag : Flags & ~Flag;
	}

	void CopyInput(ImGuiIO& IO, const FImGuiInputState& InputState)
	{
		static const uint32 LeftControl = GetKeyIndex(EKeys::LeftControl);
		static const uint32 RightControl = GetKeyIndex(EKeys::RightControl);
		static const uint32 LeftShift = GetKeyIndex(EKeys::LeftShift);
		static const uint32 RightShift = GetKeyIndex(EKeys::RightShift);
		static const uint32 LeftAlt = GetKeyIndex(EKeys::LeftAlt);
		static const uint32 RightAlt = GetKeyIndex(EKeys::RightAlt);

		// Copy key modifiers.
		IO.KeyCtrl = InputState.IsControlDown();
		IO.KeyShift = InputState.IsShiftDown();
		IO.KeyAlt = InputState.IsAltDown();
		IO.KeySuper = false;

		// Copy buffers.
		if (!InputState.GetKeysUpdateRange().IsEmpty())
		{
			for (const auto& KeyDownEvent : InputState.KeyDownEvents)
			{
				IO.AddKeyEvent(MapKey(KeyDownEvent.GetKey()), true);
			}
			
			for (const auto& KeyUpEvent : InputState.KeyUpEvents)
			{
				IO.AddKeyEvent(MapKey(KeyUpEvent.GetKey()), false);
			}
		}

		if (!InputState.GetMouseButtonsUpdateRange().IsEmpty())
		{
			Copy(InputState.GetMouseButtons(), IO.MouseDown, InputState.GetMouseButtonsUpdateRange());
		}

		for (const TCHAR Char : InputState.GetCharacters())
		{
			IO.AddInputCharacter(CastInputChar(Char));
		}

		if (InputState.IsGamepadNavigationEnabled() && InputState.HasGamepad())
		{
			for (const auto& AnalogInputEvent : InputState.AnalogInputEvents)
			{
				IO.AddKeyAnalogEvent(MapAxis(AnalogInputEvent.GetKey(),AnalogInputEvent.GetAnalogValue()), true, FMath::Abs(AnalogInputEvent.GetAnalogValue()));
			}
		}

		SetFlag(IO.ConfigFlags, ImGuiConfigFlags_NavEnableKeyboard, InputState.IsKeyboardNavigationEnabled());
		SetFlag(IO.ConfigFlags, ImGuiConfigFlags_NavEnableGamepad, InputState.IsGamepadNavigationEnabled());
		SetFlag(IO.BackendFlags, ImGuiBackendFlags_HasGamepad, InputState.HasGamepad());

		// Check whether we need to draw cursor.
		IO.MouseDrawCursor = InputState.HasMousePointer();

		// If touch is enabled and active, give it a precedence.
		if (InputState.IsTouchActive())
		{
			// Copy the touch position to mouse position.
			IO.MousePos.x = InputState.GetTouchPosition().X;
			IO.MousePos.y = InputState.GetTouchPosition().Y;

			// With touch active one frame longer than it is down, we have one frame to processed touch up.
			IO.MouseDown[0] = InputState.IsTouchDown();
		}
		else
		{
			// Copy the mouse position.
			IO.MousePos.x = InputState.GetMousePosition().X;
			IO.MousePos.y = InputState.GetMousePosition().Y;

			// Copy mouse wheel delta.
			IO.MouseWheel += InputState.GetMouseWheelDelta();
		}
	}
}
