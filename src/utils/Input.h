#pragma once
#include <utility>
#include <GLFW/glfw3.h>

namespace OpenGLEngine {
	class Input {
	public:
	public:
		static bool IsKeyPressed(GLFWwindow* windowHandler, int keyCode);
		static bool IsMouseButtonPressed(GLFWwindow* windowHandler, int button);
		static std::pair<float, float> GetMousePosition(GLFWwindow* windowHandler);
		static float GetMouseX(GLFWwindow* windowHandler);
		static float GetMouseY(GLFWwindow* windowHandler);
	};
}
