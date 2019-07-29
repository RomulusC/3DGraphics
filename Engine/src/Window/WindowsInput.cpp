#include "egpch.h"
#include "Window/WindowsInput.h"

#include <Application.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == (GLFW_PRESS==1 || GLFW_REPEAT==1);
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { float(xPos), float(yPos) };
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosition();
		return x;

	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}

}

