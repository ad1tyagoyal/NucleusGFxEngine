#pragma once
#include "src/utils/Layer.h"

namespace OpenGLEngine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override;
		void OnDetach() override;
		virtual void OnImguiRender() override;

		void Begin();
		void End();

	public:
		float m_Time = 0.0f;
	};

	
}

