#include "src/utils/Application.h"
#include "src/utils/primitive_shapes/PrimitiveShapes.h"
#include "glm/gtc/matrix_transform.hpp"

class ExampleLayer : public OpenGLEngine::Layer {
public:
	ExampleLayer()
		:nativeWindow(OpenGLEngine::Application::GetApplication().GetWindow().GetNativeWindow()),
		m_PerspectiveCamera(55.0f, 1.78, 1.0f, 500.0f), m_BoxTexture("src/res/container_diffuse.jpeg"), 
		m_GrassTexture("src/res/Grass_Texture.png", 1, GL_REPEAT, GL_REPEAT), m_Mesh() {
		OpenGLEngine::Renderer2D::Init();
		m_PerspectiveCamera.SetPosition({ 0.0f, 0.0f, -10.0f });
		m_PerspectiveCamera.SetTarget({ 0.0f, 0.0f, 0.0f });
		m_PerspectiveCamera.SetSpeed(20.0f);
		m_PerspectiveCamera.SetSensitivity(0.5f);
		OpenGLEngine::MeshGenerator::GenerateMesh(&m_Mesh, 50, 50, 1, 4.0f, 3, 2.6f, 0.0f, true);
		m_Mesh.InitComponents();
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

		m_Mesh.BindMesh();
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rot = { 0.0f, 0.0f, 0.1f };
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(glm::length(0.0f)), glm::normalize(rot))
			* glm::scale(glm::mat4(1.0f), glm::vec3(1.0f) * 1.0f);

		m_GrassTexture.Bind();
		OpenGLEngine::Shader* simpleTextureShader = new OpenGLEngine::Shader("src/res/SimpleTextureShader.shader");
		simpleTextureShader->Bind();
		simpleTextureShader->SetUniformMatrix4fv("u_ViewProjectionMatrix", 1, GL_FALSE, glm::value_ptr(m_PerspectiveCamera.GetViewProjectionMatrix()));
		simpleTextureShader->SetUniformMatrix4fv("u_TransformMat", 1, GL_FALSE, glm::value_ptr(transform));
		simpleTextureShader->SetUniform4f("u_TintColor", 1.0f, 1.0f, 1.0f, 1.0f);
		simpleTextureShader->SetUniform1i("u_Texture", 1);

		OpenGLEngine::Renderer::DrawElements(m_Mesh.GetVertexArray());
		
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
	OpenGLEngine::Texture m_GrassTexture;
	OpenGLEngine::Mesh m_Mesh;
	std::shared_ptr<OpenGLEngine::Shader> m_MeshShader;

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
