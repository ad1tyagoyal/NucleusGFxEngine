#pragma once

#include <memory>

#include "src/interface/IApplication.h"

#include "src/utils/OpenGLWindow.h";
#include "src/utils/VertexArray.h";

#include "src/utils/Buffer.h";
#include "src/utils/Shader.h";
#include "src/utils/OrthographicCamera.h";


class OpenGLEngine : public IApplication {
public:
	OpenGLEngine();
	virtual ~OpenGLEngine() override;
	virtual void OnUpdate() override;

private:

	std::shared_ptr<OpenGLWindow> m_Window;
	std::shared_ptr <VertexArray> m_VertexArraySquare;
	std::shared_ptr <VertexArray> m_VertexArrayTriangle;

	std::shared_ptr <VertexBuffer> triangleVertexBuffer;
	std::shared_ptr<VertexBuffer> squareVertexBuffer;
	
	std::shared_ptr <IndexBuffer> triangleIndexBuffer;
	std::shared_ptr<IndexBuffer> squareIndexBuffer;

	std::shared_ptr <Shader> m_Shader;

	OrthographicCamera m_OrthographicCamera;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0, 0.0f };
	float m_CameraRotationZ = 0.0f;

	float m_CamMovingSpeed = 0.1f;
	float m_CamRotationSpeed = 0.1f;
};

