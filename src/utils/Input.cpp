#include "Input.h"

bool Input::IsKeyPressed(GLFWwindow* windowHandler, int keyCode) {
	int state = glfwGetKey(windowHandler, keyCode);
	return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool Input::IsMouseButtonPressed(GLFWwindow* windowHandler, int button) {
	int state = glfwGetMouseButton(windowHandler, button);
	return (state == GLFW_PRESS);
}

std::pair<float, float> Input::GetMousePosition(GLFWwindow* windowHandler) {
	double xPos, yPos;
	glfwGetCursorPos(windowHandler, &xPos, &yPos);
	return {(float)xPos, (float) yPos };
}

float Input::GetMouseX(GLFWwindow* windowHandler) {
	std::pair<float, float> mousePos = GetMousePosition(windowHandler);
	return mousePos.first;
}

float Input::GetMouseY(GLFWwindow* windowHandler) {
	std::pair<float, float> mousePos = GetMousePosition(windowHandler);
	return mousePos.second;
}
