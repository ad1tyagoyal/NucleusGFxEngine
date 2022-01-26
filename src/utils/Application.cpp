#include "Application.h"

namespace OpenGLEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;
		m_Window.reset(new OpenGLWindow(1920.0f, 1080.0f));
		Renderer::Init();
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		while (!glfwWindowShouldClose(m_Window->GetNativeWindow())) {
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			/*m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack) {
				layer->OnImguiRender();
			}
			m_ImGuiLayer->End();*/
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}
}
