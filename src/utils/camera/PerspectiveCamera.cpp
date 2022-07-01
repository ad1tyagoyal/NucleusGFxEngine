#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


namespace OpenGLEngine {

	PerspectiveCamera::PerspectiveCamera(float fovyInDegrees, float aspectRatio, float nearZ, float farZ) {
		m_ProjectionMat = glm::perspective(glm::radians(fovyInDegrees), aspectRatio, nearZ, farZ);
		
		m_LastX = Application::GetApplication().GetWindow().GetWidth() / 2;
		m_LastY = Application::GetApplication().GetWindow().GetHeight() / 2;
	}

	PerspectiveCamera::~PerspectiveCamera() {
		delete &m_CamPosition;
		delete &m_CamDirection;
		delete &m_CamUp;
		
		delete &m_ProjectionMat;
		delete &m_ViewMat;
		delete &m_ProjectionViewMat;
		
		delete &m_CamSpeed;
		delete &m_CamSensitivity;
	}

	void PerspectiveCamera::ProcessInput(GLFWwindow* window) {
		//keyboard input
		if (OpenGLEngine::Input::IsKeyPressed(window, GLFW_KEY_W))
			m_CamPosition += m_CamSpeed * m_CamDirection * TimeStamp::GetDeltaTime();
		if (OpenGLEngine::Input::IsKeyPressed(window, GLFW_KEY_S))
			m_CamPosition -= m_CamSpeed * m_CamDirection * TimeStamp::GetDeltaTime();
		if (OpenGLEngine::Input::IsKeyPressed(window, GLFW_KEY_A))
			m_CamPosition -= glm::normalize(glm::cross(m_CamDirection, m_CamUp)) * m_CamSpeed * TimeStamp::GetDeltaTime();
		if (OpenGLEngine::Input::IsKeyPressed(window, GLFW_KEY_D))
			m_CamPosition += glm::normalize(glm::cross(m_CamDirection, m_CamUp)) * m_CamSpeed * TimeStamp::GetDeltaTime();

		//mouse input
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		float xoffset = xPos - m_LastX;
		float yoffset = m_LastY - yPos;
		m_LastX = xPos;
		m_LastY = yPos;

		xoffset *= m_CamSensitivity;
		yoffset *= m_CamSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CamDirection = glm::normalize(direction);

		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetPosition(glm::vec3 position) {
		m_CamPosition = position;
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetTarget(glm::vec3 targetPos) {
		m_CamDirection = glm::normalize(targetPos - m_CamPosition);
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::RecalculateViewMatrix() {
		m_ViewMat = glm::lookAt(m_CamPosition, m_CamPosition + m_CamDirection, m_CamUp);
		m_ProjectionViewMat = m_ProjectionMat * m_ViewMat;
	}
}

