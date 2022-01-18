#include "OpenGLEngine.h"
#include <glm/gtc/type_ptr.hpp>

#include "src/utils/Renderer.h"
#include "src/utils/VertexBufferLayout.h";

#include "src/utils/Input.h" 



OpenGLEngine::OpenGLEngine()
	:m_OrthographicCamera(-5.0f, 5.0f, -2.8125f, 2.8125f) {
	m_Window.reset(new OpenGLWindow(1920.0f, 1080.0f));

	float triangleVertices[] = {
	   -0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.0f,   0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f
	};

	unsigned int triangleIndices[] = {0, 1, 2};
	
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
	VertexBufferLayout layout;
	layout.Push<float>(3, "Positions");
	layout.Push<float>(3, "Colors");


	{
		m_VertexArrayTriangle.reset(new VertexArray());
		m_VertexArrayTriangle->Bind();
		triangleVertexBuffer.reset(new VertexBuffer(sizeof(triangleVertices), triangleVertices));
		triangleVertexBuffer->SetLayout(layout);
		triangleVertexBuffer->Bind();
		m_VertexArrayTriangle->AddVertexBuffer(triangleVertexBuffer);
		triangleIndexBuffer.reset(new IndexBuffer(3, triangleIndices));
		m_VertexArrayTriangle->SetIndexBuffer(triangleIndexBuffer);

	}
	{
		m_VertexArraySquare.reset(new VertexArray());
		m_VertexArraySquare->Bind();
		squareVertexBuffer.reset(new VertexBuffer(sizeof(squareVertices), squareVertices));
		squareVertexBuffer->SetLayout(layout);
		squareVertexBuffer->Bind();
		m_VertexArraySquare->AddVertexBuffer(squareVertexBuffer);
		squareIndexBuffer.reset(new IndexBuffer(6, squareIndices));
		m_VertexArraySquare->SetIndexBuffer(squareIndexBuffer);

	}

	

	m_Shader.reset(new Shader("src/res/BasicShader.shader"));
	m_Shader->Bind();
}

OpenGLEngine::~OpenGLEngine()
{
}

void OpenGLEngine::OnUpdate() {
	while (!glfwWindowShouldClose(m_Window->GetWindow())) {

		if (Input::IsKeyPressed(m_Window->GetWindow(), GLFW_KEY_W))
			m_CameraPosition.y += m_CamMovingSpeed;
		if(Input::IsKeyPressed(m_Window->GetWindow(), GLFW_KEY_A))
			m_CameraPosition.x -= m_CamMovingSpeed;
		if(Input::IsKeyPressed(m_Window->GetWindow(), GLFW_KEY_S))
			m_CameraPosition.y -= m_CamMovingSpeed;
		if(Input::IsKeyPressed(m_Window->GetWindow(), GLFW_KEY_D))
			m_CameraPosition.x += m_CamMovingSpeed;

		if(Input::IsKeyPressed(m_Window->GetWindow(), GLFW_KEY_O))
			m_CameraRotationZ += m_CamRotationSpeed;
		if(Input::IsKeyPressed(m_Window->GetWindow(), GLFW_KEY_P))
			m_CameraRotationZ -= m_CamRotationSpeed;


		Renderer::BeginScene({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_OrthographicCamera.SetPosition(m_CameraPosition);
		m_OrthographicCamera.SetRotation(m_CameraRotationZ);
		m_Shader->SetUniformMatrix4fv("u_ViewProjectionMatrix", 1, GL_FALSE, glm::value_ptr(m_OrthographicCamera.GetViewProjectionMatrix()));
		Renderer::DrawElements(m_VertexArraySquare);
		Renderer::DrawElements(m_VertexArrayTriangle);

		Renderer::EndScene(m_Window->GetWindow());
	}
}
