#pragma once

#include "src/interface/IApplication.h"

#include "src/utils/OpenGLWindow.h"
#include "src/utils/VertexArray.h" 
#include "src/utils/VertexBufferLayout.h"
#include "src/utils/Shader.h"
#include "src/utils/Buffer.h"

#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "src/utils/Texture.h"



class LightingColor : public IApplication {
public:
	LightingColor(glm::vec3 lightColor, glm::vec3 objectColor, glm::vec3 lightPosition, glm::vec3 objectPosition);
	virtual ~LightingColor() override;

	virtual void OnUpdate() override;

private:
	OpenGLWindow* m_OpenGLWindow;
	VertexArray* m_VAO;
	Shader* m_LightShader;
	Shader* m_ObjectShader;
	VertexBuffer* m_CubeVertices;
	Texture* containerDiffuseTexture;
	Texture* containerSpecularTexture;


	glm::vec3 m_LightColor, m_ObjectColor;
	glm::vec3 m_LightPosition, m_ObjectPosition;

};

