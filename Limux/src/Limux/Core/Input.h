#pragma once

#include "Limux/Core/Core.h"
#include "glm/glm.hpp"

namespace LMX
{
	class LMX_API Input
	{
	public:
		virtual ~Input() = default;
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> SetMousePosition(float x, float y) { return s_Instance->SetMousePositionImpl(x,y); }
		inline static float SetMouseX(float x) { return s_Instance->SetMouseXImpl(x); }
		inline static float SetMouseY(float y) { return s_Instance->SetMouseYImpl(y); }
		static enum class InputType
		{
			CURSOR,
		};
		static enum class InputMode
		{
			CURSOR_NORMAL,
			CURSOR_HIDDEN,
			CURSOR_DISABLED
		};
		inline static void SetInputMode(InputType inptype, InputMode mode){return s_Instance->SetInputModeImpl(inptype, mode);}
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> SetMousePositionImpl(float x, float y) = 0;
		virtual float SetMouseXImpl(float x) = 0;
		virtual float SetMouseYImpl(float y) = 0;
		virtual void SetInputModeImpl(InputType inptype, InputMode mode) = 0;
	private:
		static Input* s_Instance;
	};

}