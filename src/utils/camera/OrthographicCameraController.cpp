#include "OrthographicCameraController.h"


namespace OpenGLEngine {

	OrthographicCameraController::OrthographicCameraController(OrthographicCamera& camera) 
		: m_CameraPosition({0.0f, 0.0f, 0.0f}), m_CameraRotationZ(0.0f), m_Cam(camera), 
			m_Window(Application::GetApplication().GetWindow().GetNativeWindow()) {
	}
	
	void OrthographicCameraController::UpdateCamera() {
		if (OpenGLEngine::Input::IsKeyPressed(m_Window, GLFW_KEY_W))
			m_CameraPosition.y += m_CamMovingSpeed * OpenGLEngine::TimeStamp::GetDeltaTime();
		if (OpenGLEngine::Input::IsKeyPressed(m_Window, GLFW_KEY_A))
			m_CameraPosition.x -= m_CamMovingSpeed * OpenGLEngine::TimeStamp::GetDeltaTime();
		if (OpenGLEngine::Input::IsKeyPressed(m_Window, GLFW_KEY_S))
			m_CameraPosition.y -= m_CamMovingSpeed * OpenGLEngine::TimeStamp::GetDeltaTime();
		if (OpenGLEngine::Input::IsKeyPressed(m_Window, GLFW_KEY_D))
			m_CameraPosition.x += m_CamMovingSpeed * OpenGLEngine::TimeStamp::GetDeltaTime();

		if (OpenGLEngine::Input::IsKeyPressed(m_Window, GLFW_KEY_O))
			m_CameraRotationZ += m_CamRotationSpeed * OpenGLEngine::TimeStamp::GetDeltaTime();
		if (OpenGLEngine::Input::IsKeyPressed(m_Window, GLFW_KEY_P))
			m_CameraRotationZ -= m_CamRotationSpeed * OpenGLEngine::TimeStamp::GetDeltaTime();

		m_Cam.SetPosition(m_CameraPosition);
		m_Cam.SetRotation(m_CameraRotationZ);
	}

}