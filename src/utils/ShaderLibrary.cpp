#include "ShaderLibrary.h"

namespace OpenGLEngine {

	void ShaderLibrary::AddShader(const std::string& name, Shader* shader) {
		m_Shaders[name] = shader;
	}
	
	Shader* ShaderLibrary::LoadShader(const std::string& name, const std::string& filePath) {
		Shader* shader = new Shader(filePath);
		AddShader(name, shader);
		return shader;
	}
}
