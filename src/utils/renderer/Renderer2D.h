#pragma once

#include "src/utils/VertexArray.h"
#include "src/utils/Shader.h"
#include "src/utils/Buffer.h"
#include "src/utils/ShaderLibrary.h"



namespace OpenGLEngine {
	 

	static class Renderer2D {
	public:
		static void Init();
		static void BeginScene(glm::vec4 color);
		static void EndScene(GLFWwindow* nativeWindow);
		static void ShutDown();
		static void DrawVertexArrays();
		static void UpdateShaderData(glm::mat4 vpMat);
	};

}

