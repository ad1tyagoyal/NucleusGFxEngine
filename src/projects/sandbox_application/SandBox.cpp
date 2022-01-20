#include "src/utils/Application.h"

class ExampleLayer : public OpenGLEngine::Layer {
public:
	ExampleLayer() 
		: nativeWindow(OpenGLEngine::Application::GetApplication().GetWindow().GetNativeWindow()),
		m_OrthographicCamera(-5.0f, 5.0f, -2.8125f, 2.8125f),
		m_CameraPosition({0.0f, 0.0f, 0.0f}), m_CameraRotationZ(0.0f) {
		

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
			m_VertexArrayTriangle.reset(new OpenGLEngine::VertexArray());
			m_VertexArrayTriangle->Bind();
			triangleVertexBuffer.reset(new OpenGLEngine::VertexBuffer(sizeof(triangleVertices), triangleVertices));
			triangleVertexBuffer->SetLayout(layout);
			triangleVertexBuffer->Bind();
			m_VertexArrayTriangle->AddVertexBuffer(triangleVertexBuffer);
			triangleIndexBuffer.reset(new OpenGLEngine::IndexBuffer(3, triangleIndices));
			m_VertexArrayTriangle->SetIndexBuffer(triangleIndexBuffer);

		}
		{
			m_VertexArraySquare.reset(new OpenGLEngine::VertexArray());
			m_VertexArraySquare->Bind();
			squareVertexBuffer.reset(new OpenGLEngine::VertexBuffer(sizeof(squareVertices), squareVertices));
			squareVertexBuffer->SetLayout(layout);
			squareVertexBuffer->Bind();
			m_VertexArraySquare->AddVertexBuffer(squareVertexBuffer);
			squareIndexBuffer.reset(new OpenGLEngine::IndexBuffer(6, squareIndices));
			m_VertexArraySquare->SetIndexBuffer(squareIndexBuffer);

		}



		m_Shader.reset(new OpenGLEngine::Shader("src/res/BasicShader.shader"));
		m_Shader->Bind();
	}
	
	~ExampleLayer() {

	}

	virtual void OnAttach() override {
	}
	
	virtual void OnUpdate() override {
		if (OpenGLEngine::Input::IsKeyPressed(nativeWindow, GLFW_KEY_W))
			m_CameraPosition.y += m_CamMovingSpeed;
		if (OpenGLEngine::Input::IsKeyPressed(nativeWindow, GLFW_KEY_A))
			m_CameraPosition.x -= m_CamMovingSpeed;
		if (OpenGLEngine::Input::IsKeyPressed(nativeWindow, GLFW_KEY_S))
			m_CameraPosition.y -= m_CamMovingSpeed;
		if (OpenGLEngine::Input::IsKeyPressed(nativeWindow, GLFW_KEY_D))
			m_CameraPosition.x += m_CamMovingSpeed;

		if (OpenGLEngine::Input::IsKeyPressed(nativeWindow, GLFW_KEY_O))
			m_CameraRotationZ += m_CamRotationSpeed;
		if (OpenGLEngine::Input::IsKeyPressed(nativeWindow, GLFW_KEY_P))
			m_CameraRotationZ -= m_CamRotationSpeed;


		OpenGLEngine::Renderer::BeginScene({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_OrthographicCamera.SetPosition(m_CameraPosition);
		m_OrthographicCamera.SetRotation(m_CameraRotationZ);
		m_Shader->SetUniformMatrix4fv("u_ViewProjectionMatrix", 1, GL_FALSE, glm::value_ptr(m_OrthographicCamera.GetViewProjectionMatrix()));
		OpenGLEngine::Renderer::DrawElements(m_VertexArraySquare);
		OpenGLEngine::Renderer::DrawElements(m_VertexArrayTriangle);

		OpenGLEngine::Renderer::EndScene(nativeWindow);

	}
	
	virtual void OnDetach() override {
	}
	
	virtual void OnImguiRender() override{
		std::cout << this->GetName() << " On ImGui Render" << std::endl;
	}

private:

	GLFWwindow* nativeWindow;

	std::shared_ptr <OpenGLEngine::VertexArray> m_VertexArraySquare;
	std::shared_ptr <OpenGLEngine::VertexArray> m_VertexArrayTriangle;

	std::shared_ptr <OpenGLEngine::VertexBuffer> triangleVertexBuffer;
	std::shared_ptr <OpenGLEngine::VertexBuffer> squareVertexBuffer;

	std::shared_ptr <OpenGLEngine::IndexBuffer> triangleIndexBuffer;
	std::shared_ptr <OpenGLEngine::IndexBuffer> squareIndexBuffer;

	std::shared_ptr <OpenGLEngine::Shader> m_Shader;

	OpenGLEngine::OrthographicCamera m_OrthographicCamera;

	glm::vec3 m_CameraPosition;
	float m_CameraRotationZ;

	float m_CamMovingSpeed = 0.1f;
	float m_CamRotationSpeed = 0.1f;
};



class SandBox : public OpenGLEngine::Application {
public:
	SandBox() 
		: Application() {
		PushLayer(new ExampleLayer());
	}

	~SandBox() {

	}
};

int main() {
	SandBox* sandbox = new SandBox();
	sandbox->Run();
	delete sandbox;
}
