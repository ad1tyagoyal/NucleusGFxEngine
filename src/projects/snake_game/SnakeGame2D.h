#pragma once

#include <iostream>
#include <vector>

#include "src/utils/OpenGLWindow.h"
#include "src/utils/Buffer.h"
#include "src/utils/VertexArray.h"
#include "src/utils/VertexBufferLayout.h"
#include "src/utils/Shader.h"

#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



#include "src/interface/IApplication.h"



class SnakeGame2D : public IApplication {
public:
	SnakeGame2D();
	~SnakeGame2D();

	virtual void OnUpdate() override;

	void UpdatePartsPosition();
	void RenderGFx();
	float Random(float min, float max);

private:
	OpenGLWindow* m_OpenGLWindow;
	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_IBO;
	Shader* m_Shader;
};

