#pragma once
#include "vendor/stb_image/stb_image.h"

namespace OpenGLEngine {
	class Texture {
	public:
		Texture(const std::string& filePath, int slot = 0, int wrapModeS = GL_CLAMP_TO_EDGE, int wrapModeT = GL_CLAMP_TO_EDGE);
		~Texture();

		void Bind();
		void UnBind();

	private:
		unsigned int m_RendererID;
		int m_Width, m_Height, m_BPP, m_Slot;
		unsigned char* m_Data;
	};

}