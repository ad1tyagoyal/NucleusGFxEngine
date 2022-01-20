#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Texture.h"

namespace OpenGLEngine {
	Texture::Texture(const std::string& filePath, int slot, int wrapModeS, int wrapModeT)
		: m_RendererID(0), m_Width(0), m_Height(0), m_BPP(0), m_Slot(slot), m_Data(nullptr) {
		stbi_set_flip_vertically_on_load(1);
		m_Data = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_RendererID);
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_Data) stbi_image_free(m_Data);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind() {
		glActiveTexture(GL_TEXTURE0 + m_Slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Texture::UnBind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}