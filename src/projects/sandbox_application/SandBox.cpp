#include "src/utils/Application.h"
#include "src/utils/primitive_shapes/PrimitiveShapes.h"


class ExampleLayer : public OpenGLEngine::Layer {
public:
	ExampleLayer() 
		: nativeWindow(OpenGLEngine::Application::GetApplication().GetWindow().GetNativeWindow()),
		m_OrthographicCamera(-5.0f, 5.0f, -2.8125f, 2.8125f), m_OrthographicCameraController(m_OrthographicCamera) {
		OpenGLEngine::Renderer2D::Init();
	}
	
	~ExampleLayer() {

	}

	virtual void OnAttach() override {
	}
	
	virtual void OnUpdate() override {
		


		OpenGLEngine::TimeStamp::SceneStart();
		OpenGLEngine::Renderer2D::BeginScene({ 0.0f, 0.0f, 0.0f, 1.0f });
		
		m_OrthographicCameraController.UpdateCamera();
		OpenGLEngine::Renderer2D::UpdateShaderData(m_OrthographicCameraController.GetCamera().GetViewProjectionMatrix());
		OpenGLEngine::Renderer2D::DrawVertexArrays();
		
		OpenGLEngine::Renderer2D::EndScene(nativeWindow);
		OpenGLEngine::TimeStamp::SceneEnd();

	}
	
	virtual void OnDetach() override {
	}
	
	virtual void OnImguiRender() override{
		std::cout << this->GetName() << " On ImGui Render" << std::endl;
	}

private:

	GLFWwindow* nativeWindow;
	OpenGLEngine::OrthographicCamera m_OrthographicCamera;
	OpenGLEngine::OrthographicCameraController m_OrthographicCameraController;
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
