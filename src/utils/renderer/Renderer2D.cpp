#include "Renderer2D.h"
#include <glm/gtc/type_ptr.hpp>

namespace OpenGLEngine {



	struct Renderer2DStorage {
		/*std::shared_ptr <OpenGLEngine::VertexArray> m_VertexArraySquare;
		std::shared_ptr <OpenGLEngine::VertexArray> m_VertexArrayTriangle;

		std::shared_ptr <OpenGLEngine::VertexBuffer> triangleVertexBuffer;
		std::shared_ptr <OpenGLEngine::VertexBuffer> squareVertexBuffer;

		std::shared_ptr <OpenGLEngine::IndexBuffer> triangleIndexBuffer;
		std::shared_ptr <OpenGLEngine::IndexBuffer> squareIndexBuffer;*/

		std::shared_ptr<VertexArray> m_VertexArrays;

		OpenGLEngine::ShaderLibrary m_ShaderLibrary;
	};

	struct ShaderData {
		//projection * View
		glm::mat4 m_ViewProjectionMat;
	};
	
	static Renderer2DStorage s_Data;
	static ShaderData s_ShaderData;

	void Renderer2D::Init() {
		float triangleVertices[] = {
		   -0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f,   0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		unsigned int triangleIndices[] = { 0, 1, 2 };

		float squareVertices[] = {
		   -1.5f, -1.5f, -1.0f, 0.2f, 0.3f, 0.4f,
		   -1.5f,  -0.5f, -1.0f, 0.5f, 0.6f, 0.7f,
			-0.5f,  -0.5f, -1.0f, 0.8f, 0.9f, 0.1f,
			-0.5f, -1.5f, -1.0f, 0.2f, 0.4f, 0.6f,
		};

		unsigned int squareIndices[] = {
			0, 1, 2,
			2, 3, 0
		};

		//layout for both triangle and square
		OpenGLEngine::VertexBufferLayout layout;
		layout.Push<float>(3, "Positions");
		layout.Push<float>(3, "Colors");

		{
			s_Data.m_VertexArrays.reset(new OpenGLEngine::VertexArray());
			s_Data.m_VertexArrays->Bind();
			
			std::shared_ptr<VertexBuffer> _triangleVertexBuffer;
			_triangleVertexBuffer.reset(new OpenGLEngine::VertexBuffer(sizeof(triangleVertices), triangleVertices));
			_triangleVertexBuffer->SetLayout(layout);
			_triangleVertexBuffer->Bind();
			s_Data.m_VertexArrays->AddVertexBuffer(_triangleVertexBuffer);

			std::shared_ptr<IndexBuffer> _triangleIndexBuffer;
			_triangleIndexBuffer.reset(new OpenGLEngine::IndexBuffer(3, triangleIndices));
			s_Data.m_VertexArrays->SetIndexBuffer(_triangleIndexBuffer);
		}
		/*{
			s_Data.m_VertexArraySquare.reset(new OpenGLEngine::VertexArray());
			s_Data.m_VertexArraySquare->Bind();
			s_Data.squareVertexBuffer.reset(new OpenGLEngine::VertexBuffer(sizeof(squareVertices), squareVertices));
			s_Data.squareVertexBuffer->SetLayout(layout);
			s_Data.squareVertexBuffer->Bind();
			s_Data.m_VertexArraySquare->AddVertexBuffer(s_Data.squareVertexBuffer);
			s_Data.squareIndexBuffer.reset(new OpenGLEngine::IndexBuffer(6, squareIndices));
			s_Data.m_VertexArraySquare->SetIndexBuffer(s_Data.squareIndexBuffer);

		}*/

		OpenGLEngine::Shader* shader = s_Data.m_ShaderLibrary.LoadShader("BasicShader", "src/res/BasicShader.shader");
		shader->Bind();
	}

	void Renderer2D::BeginScene(glm::vec4 color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer2D::EndScene(GLFWwindow* nativeWindow) {
		glfwSwapBuffers(nativeWindow);
		glfwPollEvents();
	}

	void Renderer2D::ShutDown() {
		delete &s_Data;
	}

	void Renderer2D::DrawVertexArrays() {
		OpenGLEngine::Shader* _shader = s_Data.m_ShaderLibrary.Get("BasicShader");
		_shader->Bind();
		_shader->SetUniformMatrix4fv("u_ViewProjectionMatrix", 1, GL_FALSE, glm::value_ptr(s_ShaderData.m_ViewProjectionMat));

		s_Data.m_VertexArrays->Bind();
		glDrawElements(GL_TRIANGLES, s_Data.m_VertexArrays->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

		//for (int i = 0; i < s_Data.m_VertexArrays.size(); i++) {
		//	//2D Renderer specific optimizations
		//	std::shared_ptr<VertexArray>& _vertexArray = s_Data.m_VertexArrays[i];
		//	_vertexArray->Bind();
		//	glDrawElements(GL_TRIANGLES, _vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

		//}
	}

	void Renderer2D::UpdateShaderData(glm::mat4 vpMat) {
		s_ShaderData.m_ViewProjectionMat = vpMat;
	}

}

