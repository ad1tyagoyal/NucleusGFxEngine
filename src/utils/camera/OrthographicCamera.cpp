#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace OpenGLEngine {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -5.0f, 5.0f);
		RecalculateViewMatrix();
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::SetPosition(glm::vec3 position) {
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotationZ) {
		m_RotationZ = rotationZ;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix() {
		glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationZ), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transformMatrix);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}