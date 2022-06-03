#include "Renderer2D.h"
#include <glm/gtc/type_ptr.hpp>

namespace OpenGLEngine {



	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> m_VertexArrays;
		std::shared_ptr<VertexArray> m_TexQuadVA;
		OpenGLEngine::ShaderLibrary m_ShaderLibrary;
	};

	struct ShaderData {
		glm::mat4 m_ViewProjectionMat;
	};
	
	static Renderer2DStorage s_Data;
	static ShaderData s_ShaderData;

	void Renderer2D::Init() {

		float squareVertices[] = {
			0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 2.0f, -1.0f, 0.0f, 1.0f,
			2.0f, 2.0f, -1.0f, 1.0f, 1.0f,
			2.0f, 0.0f, -1.0f, 1.0f, 0.0f 
		};

		unsigned int squareIndices[] = {
			0, 1, 2,
			2, 3, 0
		};

		
		OpenGLEngine::VertexBufferLayout quadLayout;
		quadLayout.Push<float>(3, "Positions");
		quadLayout.Push<float>(2, "TextCoordinates");

		{
			s_Data.m_TexQuadVA.reset(new OpenGLEngine::VertexArray());
			s_Data.m_TexQuadVA->Bind();

			std::shared_ptr<VertexBuffer> _quadVB;
			_quadVB.reset(new OpenGLEngine::VertexBuffer(sizeof(squareVertices), squareVertices));
			_quadVB->SetLayout(quadLayout);
			_quadVB->Bind();
			s_Data.m_TexQuadVA->AddVertexBuffer(_quadVB);
			
			std::shared_ptr<IndexBuffer> _quadIB;
			_quadIB.reset(new OpenGLEngine::IndexBuffer(6, squareIndices));
			s_Data.m_TexQuadVA->SetIndexBuffer(_quadIB);

		}

		s_Data.m_ShaderLibrary.LoadShader("BasicShader", "src/res/BasicShader.shader");
		s_Data.m_ShaderLibrary.LoadShader("SimpleTextureShader", "src/res/SimpleTextureShader.shader");
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
	}

	void Renderer2D::UpdateShaderData(glm::mat4 vpMat) {
		s_ShaderData.m_ViewProjectionMat = vpMat;
	}


	void Renderer2D::DrawQuad(float scale, glm::vec3 position, glm::vec3 rotation) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
								* glm::rotate(glm::mat4(1.0f), glm::radians(glm::length(rotation)), glm::normalize(rotation))
								* glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) * scale);
		s_Data.m_VertexArrays->Bind();
		OpenGLEngine::Shader* _shader = s_Data.m_ShaderLibrary.Get("BasicShader");
		_shader->Bind();
		_shader->SetUniformMatrix4fv("u_ViewProjectionMatrix", 1, GL_FALSE, glm::value_ptr(s_ShaderData.m_ViewProjectionMat));
		_shader->SetUniformMatrix4fv("u_TransformMat", 1, GL_FALSE, glm::value_ptr(transform));
		s_Data.m_VertexArrays->Bind();
		glDrawElements(GL_TRIANGLES, s_Data.m_VertexArrays->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}

	void Renderer2D::DrawQuad(float scale, glm::vec3 position, glm::vec3 rotation, Texture& texture, glm::vec4 color) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
								* glm::rotate(glm::mat4(1.0f), glm::radians(glm::length(rotation)), glm::normalize(rotation))
								* glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) * scale);

		s_Data.m_TexQuadVA->Bind();
		texture.Bind();
		OpenGLEngine::Shader* simpleTextureShader = s_Data.m_ShaderLibrary.Get("SimpleTextureShader");
		simpleTextureShader->Bind();
		simpleTextureShader->SetUniformMatrix4fv("u_ViewProjectionMatrix", 1, GL_FALSE, glm::value_ptr(s_ShaderData.m_ViewProjectionMat));
		simpleTextureShader->SetUniformMatrix4fv("u_TransformMat", 1, GL_FALSE, glm::value_ptr(transform));
		simpleTextureShader->SetUniform4f("u_TintColor",color.r, color.g, color.b, color.a);
		simpleTextureShader->SetUniform1i("u_Texture",0);

		s_Data.m_TexQuadVA->Bind();
		glDrawElements(GL_TRIANGLES, s_Data.m_TexQuadVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}

