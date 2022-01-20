#include "OpenGLWindow.h"

namespace OpenGLEngine {
	OpenGLWindow::OpenGLWindow(float width, float height)
		: m_Width(width), m_Height(height) {

		if (!glfwInit()) {
			std::cout << "Failed to load GLFW!" << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(width, height, "OpenGL Learning Project", NULL, NULL);

		if (m_Window == NULL) {
			std::cout << "Failed to create OpenGL window!" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK) {
			std::cout << "Failed to load GLEW!" << std::endl;
			return;
		}

		glViewport(0, 0, m_Width, m_Height);

		/*glfwSetWindowSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height) {
				glViewport(0, 0, width, height);
			});*/
	}

	OpenGLWindow::~OpenGLWindow() {
		glfwDestroyWindow(m_Window);
	}
}
