#include "SnakeGame2D.h"

std::vector<glm::vec3> snakePartsPos;
std::vector<glm::vec4> snakePartsColor;

glm::vec3 speedVector(0.04f, 0.04f, 0.0f);
glm::vec3 foodPos;
glm::vec4 foodColor;
int dirX = 0;
int dirY = 0;

float updateInterval = 0.05f;
float deltaTime;
float lastFrameTime = 0.0f;

float timer = 0.0f;

SnakeGame2D::SnakeGame2D() {
	m_OpenGLWindow = new OpenGLWindow(960.0f, 960.0f);

	//vertex array
	m_VAO = new VertexArray();
	m_VAO->Bind();

	//vertex buffer
	float vertices[4 * 3] = {
		-0.02f, -0.02f, -0.02f,
		 0.02f, -0.02f, -0.02f,
		 0.02f,  0.02f, -0.02f,
		-0.02f,  0.02f, -0.02f
	};

	m_VBO = new VertexBuffer(sizeof(vertices), vertices);
	m_VBO->Bind();

	VertexBufferLayout layout;
	layout.Push<float>(3, "position");
	m_VAO->AddBuffer(*m_VBO, layout);

	//index buffer
	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	m_IBO = new IndexBuffer(sizeof(indices), indices);
	m_IBO->Bind();

	m_Shader = new Shader("src/res/BasicShader.shader");
	m_Shader->Bind();

	snakePartsPos.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	snakePartsColor.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glfwSetKeyCallback(m_OpenGLWindow->GetWindow(), 
		[](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (key == GLFW_KEY_W && action == GLFW_PRESS && dirY != -1) {
				dirY = 1;
				dirX = 0;
			}
			else if (key == GLFW_KEY_S && action == GLFW_PRESS && dirY != 1) {
				dirY = -1;
				dirX = 0;
			}
			else if (key == GLFW_KEY_A && action == GLFW_PRESS && dirX != 1) {
				dirX = -1;
				dirY = 0;
			}
			else if (key == GLFW_KEY_D && action == GLFW_PRESS && dirX != -1) {
				dirX = 1;
				dirY = 0;
			}
		});

	foodPos = glm::vec3((float)Random(-0.7f, 0.7f), (float)Random(-0.7f, 0.7f), 1.0f);
	foodColor = glm::vec4((float)Random(0.1f, 1.0f), (float)Random(0.1f, 1.0f), (float)Random(0.1f, 1.0f), 1.0f);

}

SnakeGame2D::~SnakeGame2D() {
	m_OpenGLWindow->~OpenGLWindow();
}

void SnakeGame2D::OnUpdate() {
	while (!glfwWindowShouldClose(m_OpenGLWindow->GetWindow())) {
		m_OpenGLWindow->BeginFrame();

		float currTime = (float)glfwGetTime();
		deltaTime = currTime - lastFrameTime;
		lastFrameTime = currTime;

		timer += deltaTime;

		if (timer >= updateInterval) {
			timer = 0.0f;
			UpdatePartsPosition();
			//check for collision with food or itself
			for (int i = 1; i < snakePartsPos.size(); i++) {
				if (snakePartsPos[0] == snakePartsPos[i]) {
					glm::vec3 headPos = snakePartsPos[0];
					glm::vec4 headColor = snakePartsColor[0];

					snakePartsPos.clear();
					snakePartsColor.clear();

					snakePartsPos.push_back(headPos);
					snakePartsColor.push_back(headColor);
				}
			}

			if (abs(snakePartsPos[0].x - foodPos.x) <= 0.04f && abs(snakePartsPos[0].y - foodPos.y) <= 0.04f) {
				//increase length and generate new food
				glm::vec3 newBlockPos = snakePartsPos[snakePartsPos.size() - 1];
				snakePartsPos.push_back(newBlockPos);
				snakePartsColor.push_back(foodColor);

				foodPos = glm::vec3((float)Random(-0.7f, 0.7f), (float)Random(-0.7f, 0.7f), 1.0f);
				foodColor = glm::vec4((float)Random(0.1f, 1.0f), (float)Random(0.1f, 1.0f), (float)Random(0.1f, 1.0f), 1.0f);
			}

		}
		RenderGFx();

		

		m_OpenGLWindow->EndFrame();
	}
	glfwTerminate();
}

float SnakeGame2D::Random(float min, float max) {
	float value = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return value;
}

void SnakeGame2D::UpdatePartsPosition() {

	for (int i = snakePartsPos.size() - 1; i >= 1; i--)
	{
		snakePartsPos[i] = snakePartsPos[(int) (i-1)];
		if (abs(snakePartsPos[i].x) >= 0.80f) snakePartsPos[i].x *= -1.0f;
		if (abs(snakePartsPos[i].y) >= 0.80f) snakePartsPos[i].y *= -1.0f;
	}
	//for head
	snakePartsPos[0] += speedVector * glm::vec3(dirX, dirY, 0.0f);	
	if (abs(snakePartsPos[0].x) >= 0.80f) snakePartsPos[0].x *= -1.0f;
	if (abs(snakePartsPos[0].y) >= 0.80f) snakePartsPos[0].y *= -1.0f;
}

void SnakeGame2D::RenderGFx() {
	//snake
	for (size_t i = 0; i < snakePartsPos.size(); i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, snakePartsPos[i]);
		m_Shader->SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
		m_Shader->SetUniform4f("v_Color", snakePartsColor[i].r, snakePartsColor[i].g, 
																	snakePartsColor[i].b, snakePartsColor[i].a);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	}

	//food
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, foodPos);
		m_Shader->SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
		m_Shader->SetUniform4f("v_Color", foodColor.r, foodColor.g, foodColor.b, foodColor.a);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	}

	//BG quad
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(40.0f, 40.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		m_Shader->SetUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
		m_Shader->SetUniform4f("v_Color", 0.8f, 0.5f, 0.5f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	}
}