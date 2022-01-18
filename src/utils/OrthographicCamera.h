#pragma once
#include <glm/glm.hpp>

class OrthographicCamera {
public:
	OrthographicCamera(float left, float right, float bottom, float top);
	~OrthographicCamera();

	void SetPosition(glm::vec3 position);
	inline glm::vec3& GetPosition() { return m_Position; }
	
	void SetRotation(float rotationZ);
	inline float GetRotation() { return m_RotationZ; }

	inline glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
	inline glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
	inline glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	
private:
	void RecalculateViewMatrix();


private:
	glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
	float m_RotationZ = 0.0f;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ViewProjectionMatrix;
};

