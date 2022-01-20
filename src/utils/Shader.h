#pragma once

#include <string>

#include <glm/mat4x4.hpp>

namespace OpenGLEngine {

	struct ShaderSrc {
		std::string vertexShader;
		std::string fragmentShader;
	};

	class Shader {
	public:
		Shader();
		Shader(const std::string& filePath);
		~Shader();

		void Bind();
		void UnBind();

		const void SetUniform4f(const char* uniformName, float v1, float v2, float v3, float v4) const;
		const void SetUniform3f(const char* uniformName, float v1, float v2, float v3) const;
		const void SetUniform1f(const char* uniformName, float v) const;
		const void SetUniform1i(const char* uniformName, int value) const;
		const void SetUniformMatrix4fv(const char* uniformName, int count, unsigned char transpose, float* value);

		inline const unsigned int GetRendererID() const { return m_RendererID; }

	private:
		void CreateShader();
		unsigned int CompileShader(unsigned int type, std::string& shaderStr);
		ShaderSrc ParseShader(const std::string& filePath);

	private:
		unsigned int m_RendererID;
		ShaderSrc m_ShaderSrc;
	};

}
