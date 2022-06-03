#pragma once
#include "src/utils/Application.h"
#include "src/utils/Input.h"
#include "src/utils/camera/OrthographicCamera.h"
#include "src/utils/TimeStamp.h"

namespace OpenGLEngine {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(OrthographicCamera& camera);
		void UpdateCamera();

		inline OrthographicCamera& GetCamera() const {
			return m_Cam;
		}

	private:
		OrthographicCamera& m_Cam;

		glm::vec3 m_CameraPosition;
		float m_CameraRotationZ;

		float m_CamMovingSpeed = 10.0f;
		float m_CamRotationSpeed = 45.0f;
		GLFWwindow* m_Window;
	};


}

