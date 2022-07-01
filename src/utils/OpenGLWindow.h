#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGLEngine {
	class OpenGLWindow {
	public:
		OpenGLWindow(float width, float height);
		~OpenGLWindow();

		void SetCursorDisable();

		inline GLFWwindow* GetNativeWindow() const { return m_Window; }
		inline float GetHeight() const { return m_Height; }
		inline float GetWidth() const { return m_Width; }

	private:
		float m_Width;
		float m_Height;
		GLFWwindow* m_Window;
	};

}