#pragma once
#include <glm/glm.hpp>
#include "src/utils/Application.h"
#include "src/utils/Input.h"
#include "src/utils/TimeStamp.h"

namespace OpenGLEngine {
	class PerspectiveCamera {
	public:
		PerspectiveCamera(float fovyInDegrees, float aspectRatio, float nearZ, float farZ);
		~PerspectiveCamera();

		void SetPosition(glm::vec3 position);
		void SetTarget(glm::vec3 targetPos); 
		inline void SetSpeed(float camSpeed) { m_CamSpeed = camSpeed; }
		inline void SetSensitivity(float camSensitivity) { m_CamSensitivity = camSensitivity; }
		
		inline glm::vec3& GetPosition() { return m_CamPosition; }
		void ProcessInput(GLFWwindow* window);

		inline glm::mat4& GetProjectionMatrix() { return m_ProjectionMat; }
		inline glm::mat4& GetViewMatrix() { return m_ViewMat; }
		inline glm::mat4& GetViewProjectionMatrix() { return m_ProjectionViewMat; }

	private:
		void RecalculateViewMatrix();


	private:
		glm::vec3 m_CamPosition = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_CamDirection = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_CamUp = { 0.0f, 1.0f, 0.0f };

		glm::mat4 m_ProjectionMat;
		glm::mat4 m_ViewMat;
		glm::mat4 m_ProjectionViewMat;

		float m_CamSpeed;
		float m_CamSensitivity;

		float m_LastX = 0.0f;
		float m_LastY = 0.0f;
		
		float m_Yaw = 0.0f;
		float m_Pitch = 0.0f;
	};

}
