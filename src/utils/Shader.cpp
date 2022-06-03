#include "Shader.h"

#include <fstream>
#include <sstream>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace OpenGLEngine {

	Shader::Shader() {
	}

	Shader::Shader(const std::string& filePath)
		: m_ShaderSrc(ParseShader(filePath)) {
		CreateShader();
	}
	Shader::~Shader() {
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() {
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind() {
		glUseProgram(0);
	}

	const void Shader::SetUniform4f(const char* uniformName, float v1, float v2, float v3, float v4) const {
		int location = glGetUniformLocation(m_RendererID, uniformName);
		glUniform4f(location, v1, v2, v3, v4);
	}

	const void Shader::SetUniform3f(const char* uniformName, float v1, float v2, float v3) const {
		int location = glGetUniformLocation(m_RendererID, uniformName);
		glUniform3f(location, v1, v2, v3);
	}

	const void Shader::SetUniform1f(const char* uniformName, float v) const {
		int location = glGetUniformLocation(m_RendererID, uniformName);
		glUniform1f(location, v);
	}

	const void Shader::SetUniform1i(const char* uniformName, int value) const {
		int location = glGetUniformLocation(m_RendererID, uniformName);
		glUniform1i(location, value);
	}

	const void Shader::SetUniformMatrix4fv(const char* uniformName, int count, unsigned char transpose, float* value) {
		int location = glGetUniformLocation(m_RendererID, uniformName);
		glUniformMatrix4fv(location, count, transpose, value);
	}

	void Shader::CreateShader() {
		m_RendererID = glCreateProgram();

		unsigned int vs = CompileShader(GL_VERTEX_SHADER, m_ShaderSrc.vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, m_ShaderSrc.fragmentShader);

		glAttachShader(m_RendererID, vs);
		glAttachShader(m_RendererID, fs);

		glLinkProgram(m_RendererID);
		glValidateProgram(m_RendererID);

		glUseProgram(m_RendererID);
	}

	unsigned int Shader::CompileShader(unsigned int type, std::string& shaderStr) {
		unsigned int shaderProgram = glCreateShader(type);
		const char* shaderSrc = shaderStr.c_str();
		glShaderSource(shaderProgram, 1, &shaderSrc, 0);
		glCompileShader(shaderProgram);
		return shaderProgram;
	}

	ShaderSrc Shader::ParseShader(const std::string& filePath) {

		enum class ShaderType {
			None = -1, Vertex = 0, Fragment = 1
		};
		std::ifstream fileStream(filePath);

		std::string line;
		std::stringstream ss[2];

		ShaderType shaderType = ShaderType::None;

		while (std::getline(fileStream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					shaderType = ShaderType::Vertex;
				else if (line.find("fragment") != std::string::npos)
					shaderType = ShaderType::Fragment;
			}
			else
				ss[(int)shaderType] << line << "\n";
		}
		return { ss[0].str(), ss[1].str() };

	}
}