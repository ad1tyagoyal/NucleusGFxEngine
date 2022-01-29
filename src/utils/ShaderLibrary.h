#pragma once

#include <unordered_map>
#include "src/utils/Shader.h"

namespace OpenGLEngine {

	class ShaderLibrary {
	public:
		void AddShader(const std::string& name, Shader* shader);
		Shader* LoadShader(const std::string& name, const std::string& filePath);

		inline Shader* Get(const std::string& name) { return m_Shaders[name]; }

	private:
		std::unordered_map<std::string, Shader*> m_Shaders;

	};

}


