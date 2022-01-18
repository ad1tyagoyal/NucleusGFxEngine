#include "Renderer.h"

void Renderer::BeginScene(BackgroundColor color) {
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::DrawElements(std::shared_ptr<VertexArray>& vertexArray) {
	vertexArray->Bind();
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount() , GL_UNSIGNED_INT, nullptr);
}


void Renderer::EndScene(GLFWwindow* window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}
