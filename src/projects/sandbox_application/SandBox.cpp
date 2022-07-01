#include "src/utils/Application.h"
#include "src/utils/primitive_shapes/PrimitiveShapes.h"


class ExampleLayer : public OpenGLEngine::Layer {
public:
	ExampleLayer()
		:nativeWindow(OpenGLEngine::Application::GetApplication().GetWindow().GetNativeWindow()),
		m_PerspectiveCamera(55.0f, 1.78, 1.0f, 100.0f), m_BoxTexture("src/res/container_diffuse.jpeg") {
		OpenGLEngine::Renderer2D::Init();
		m_PerspectiveCamera.SetPosition({ 0.0f, 0.0f, -10.0f });
		m_PerspectiveCamera.SetTarget({ 0.0f, 0.0f, 0.0f });
		m_PerspectiveCamera.SetSpeed(20.0f);
		m_PerspectiveCamera.SetSensitivity(0.5f);
	}
	
	~ExampleLayer() {

	}

	virtual void OnAttach() override {
	}
	
	virtual void OnUpdate() override {
		OpenGLEngine::Renderer2D::BeginScene({ 0.0f, 0.0f, 0.0f, 1.0f });
		OpenGLEngine::TimeStamp::SceneStart();

		OpenGLEngine::Application::GetApplication().GetWindow().SetCursorDisable();

		m_PerspectiveCamera.ProcessInput(nativeWindow);
		OpenGLEngine::Renderer2D::UpdateShaderData(m_PerspectiveCamera.GetViewProjectionMatrix());
		OpenGLEngine::Renderer2D::DrawQuad(1.0f, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.1f }, m_BoxTexture);
		OpenGLEngine::Renderer2D::DrawQuad(1.5f, { 10.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 45.0f }, m_BoxTexture);
		OpenGLEngine::Renderer2D::DrawQuad(3.0f, { 0.0f, 10.0f, 0.0f }, { 0.0f, 0.0f, 0.1f }, m_BoxTexture);
		
		OpenGLEngine::TimeStamp::SceneEnd();
		OpenGLEngine::Renderer2D::EndScene(nativeWindow);
	}
	
	virtual void OnDetach() override {
	}
	
	virtual void OnImguiRender() override{
		std::cout << this->GetName() << " On ImGui Render" << std::endl;
	}

private:
	GLFWwindow* nativeWindow;
	OpenGLEngine::PerspectiveCamera m_PerspectiveCamera;
	OpenGLEngine::Texture m_BoxTexture;
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
