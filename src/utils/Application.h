#pragma once

#include <memory>

#include "src/utils/OpenGLWindow.h";
#include "src/utils/Input.h" 
#include "src/utils/Layer.h"
//#include "src/utils/ImGui/ImGuiLayer.h"
#include "src/utils/LayerStack.h"

#include "src/utils/VertexArray.h";
#include "src/utils/Buffer.h";
#include "src/utils/camera/OrthographicCamera.h"
#include "src/utils/camera/OrthographicCameraController.h"
#include "src/utils/renderer/Renderer.h"
#include "src/utils/renderer/Renderer2D.h"
#include "src/utils/VertexBufferLayout.h";
#include "src/utils/TimeStamp.h"
#include "src/utils/ShaderLibrary.h"


#include <glm/gtc/type_ptr.hpp>

namespace OpenGLEngine {
	class Application {
	public:
		Application();
		~Application();
	
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& GetApplication() { return *s_Instance; }
		inline OpenGLWindow& GetWindow() { return *m_Window; }

	private:
		static Application* s_Instance;
		std::unique_ptr<OpenGLWindow> m_Window;
		LayerStack m_LayerStack;
		//ImGuiLayer* m_ImGuiLayer;
	};
}

