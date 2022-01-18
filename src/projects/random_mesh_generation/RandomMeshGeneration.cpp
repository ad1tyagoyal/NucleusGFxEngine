#include "RandomMeshGeneration.h"

#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

glm::mat4 view;
float yaw = -90.0f, pitch = -45.0f;
float lastX = 480.0f, lastY = 270.0f;
float senstivity = 0.1f;

glm::vec3 camUp;
glm::vec3 camPosition;
glm::vec3 camFront;
glm::vec3 camDirection;


RandomMeshGeneration::RandomMeshGeneration(int width, int length, int levelOfDetail, float scale, int octaves,
																			float lacunarity, float persistancy) {
	m_Window = new OpenGLWindow(960.0f, 960.0f);

	m_MeshGenerator = new MeshGenerator(width, length, levelOfDetail, scale, octaves, lacunarity, persistancy);

	glfwSetCursorPosCallback(m_Window->GetWindow(),
		[](GLFWwindow* window, double xPos, double yPos) {

			float xOffset = xPos - lastX;
			float yOffset = yPos - lastY;
			lastX = xPos;
			lastY = yPos;

			xOffset *= senstivity;
			yOffset *= senstivity;

			yaw += xOffset;
			pitch -= yOffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			std::cout << "yaw: " << yaw << "pitch: " << pitch << std::endl;
		});

	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	camPosition = glm::vec3(0.0f, 4.0f, 3.0f);
	camDirection = glm::vec3(0.0f, 0.0f, -1.0f);

	camDirection.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	camDirection.y = glm::sin(glm::radians(pitch));
	camDirection.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

	glm::mat4 lookAt = glm::lookAt(camPosition, camPosition + camDirection, camUp);

	//m_MeshShader->SetUniformMatrix4fv("v_View", 1, GL_FALSE, glm::value_ptr(lookAt));
}

RandomMeshGeneration::~RandomMeshGeneration() {
}

void RandomMeshGeneration::OnUpdate() {
	while (!glfwWindowShouldClose(m_Window->GetWindow())) {
		m_Window->BeginFrame();

		m_MeshGenerator->GetMesh()->Draw();

		camDirection.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
		camDirection.y = glm::sin(glm::radians(pitch));
		camDirection.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

		glm::mat4 lookAt = glm::lookAt(camPosition, camPosition + camDirection, camUp);

		//m_MeshShader->SetUniformMatrix4fv("v_View", 1, GL_FALSE, glm::value_ptr(lookAt));

		m_Window->EndFrame();
	}
	glfwTerminate();
}
