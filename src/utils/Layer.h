#pragma once
#include <string>

namespace OpenGLEngine {

	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		~Layer();
		virtual void OnAttach() {}
		virtual void OnUpdate() {}
		virtual void OnDetach() {}
		virtual void OnImguiRender() {}
		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}


