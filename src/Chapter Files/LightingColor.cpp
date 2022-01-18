#include "LightingColor.h"
#include "src/utils/Texture.h"

LightingColor::LightingColor(glm::vec3 lightColor, glm::vec3 objectColor, glm::vec3 lightPosition, glm::vec3 objectPosition)
	: m_LightColor(lightColor), m_ObjectColor(objectColor), m_LightPosition(lightPosition), m_ObjectPosition(objectPosition) {
	m_OpenGLWindow = new OpenGLWindow(1080.0f, 1080.0f);
	m_VAO = new VertexArray();
	//m_ObjectVAO = new VertexArray();

    float vertices[] = {
    -0.125f, -0.125f, -0.125f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
     0.125f, -0.125f, -0.125f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
     0.125f,  0.125f, -0.125f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
     0.125f,  0.125f, -0.125f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
    -0.125f,  0.125f, -0.125f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
    -0.125f, -0.125f, -0.125f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

    -0.125f, -0.125f,  0.125f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
     0.125f, -0.125f,  0.125f,  0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
     0.125f,  0.125f,  0.125f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
     0.125f,  0.125f,  0.125f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
    -0.125f,  0.125f,  0.125f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
    -0.125f, -0.125f,  0.125f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,

    -0.125f,  0.125f,  0.125f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.125f,  0.125f, -0.125f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.125f, -0.125f, -0.125f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.125f, -0.125f, -0.125f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.125f, -0.125f,  0.125f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.125f,  0.125f,  0.125f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

     0.125f,  0.125f,  0.125f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
     0.125f,  0.125f, -0.125f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
     0.125f, -0.125f, -0.125f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.125f, -0.125f, -0.125f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.125f, -0.125f,  0.125f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
     0.125f,  0.125f,  0.125f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

    -0.125f, -0.125f, -0.125f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     0.125f, -0.125f, -0.125f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
     0.125f, -0.125f,  0.125f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.125f, -0.125f,  0.125f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.125f, -0.125f,  0.125f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    -0.125f, -0.125f, -0.125f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

    -0.125f,  0.125f, -0.125f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
     0.125f,  0.125f, -0.125f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     0.125f,  0.125f,  0.125f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     0.125f,  0.125f,  0.125f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.125f,  0.125f,  0.125f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -0.125f,  0.125f, -0.125f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
    };
	
	m_CubeVertices = new VertexBuffer(sizeof(vertices), vertices);

	VertexBufferLayout layout;
	layout.Push<float>(3, "Position");
	layout.Push<float>(3, "Normal");
	layout.Push<float>(2, "TextureCoordinate");

	m_VAO->AddBuffer(*m_CubeVertices, layout);
	m_VAO->UnBind();

	m_LightShader = new Shader("src/res/LightingLightShader.shader");
	m_ObjectShader = new Shader("src/res/LightingObjectShader.shader");

	containerDiffuseTexture = new Texture("src/res/container_diffuse.jpeg", 0);
	containerSpecularTexture = new Texture("src/res/container_specular.jpeg", 1);
	
}

LightingColor::~LightingColor() {

}

void LightingColor::OnUpdate() {
	while (!glfwWindowShouldClose(m_OpenGLWindow->GetWindow())) {
		m_OpenGLWindow->BeginFrame();
		
		m_VAO->Bind();

		
		m_LightShader->Bind();
		glm::mat4 model = glm::mat4(1.0f);
		//m_LightPosition.y += glm::sinh((float)glfwGetTime());
		float lightX = 1.0f * sin(glfwGetTime());
		float lightY = -0.15f;
		float lightZ = 0.75f * cos(glfwGetTime());
		m_LightPosition = glm::vec3(lightX, lightY, lightZ);
		model = glm::translate(model, m_LightPosition);
		m_LightShader->SetUniformMatrix4fv("u_Model", 1, GL_FALSE, glm::value_ptr(model));



		m_LightShader->SetUniform3f("u_LightColor", m_LightColor.r, m_LightColor.g, m_LightColor.b);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		m_ObjectShader->Bind();
		model = glm::mat4(1.0f);
		model = glm::translate(model, m_ObjectPosition);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.2f, 1.0f, 0.5f));
		m_ObjectShader->SetUniformMatrix4fv("u_Model", 1, GL_FALSE, glm::value_ptr(model));

		m_ObjectShader->SetUniform3f("u_LightColor", m_LightColor.r, m_LightColor.g, m_LightColor.b);
		m_ObjectShader->SetUniform3f("u_LightPos", m_LightPosition.x, m_LightPosition.y, m_LightPosition.z);
		//m_ObjectShader->SetUniform3f("u_ObjectColor", m_ObjectColor.r, m_ObjectColor.g, m_ObjectColor.b);

		m_ObjectShader->SetUniform1f("u_Material.ambientStrength", 0.2f);
		m_ObjectShader->SetUniform1f("u_Material.shininess", 0.3f);
		
		m_ObjectShader->SetUniform3f("u_CamPos", 0.0f, 0.0f, 2.0f);

		containerDiffuseTexture->Bind();
		m_ObjectShader->SetUniform1i("u_Material.diffuse", 0);
		containerSpecularTexture->Bind();
		m_ObjectShader->SetUniform1i("u_Material.specular", 1);


		glDrawArrays(GL_TRIANGLES, 0, 36);

		m_OpenGLWindow->EndFrame();
	}
}
