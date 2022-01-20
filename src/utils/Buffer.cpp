#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Buffer.h"


namespace OpenGLEngine {

	//Vertex Buffer
	VertexBuffer::VertexBuffer(unsigned int size, float* vertices) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::UnBind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	//Index Buffer
	IndexBuffer::IndexBuffer(unsigned int count, unsigned int* indices) 
		: m_Count(count) {
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(indices), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {

	}

	void IndexBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::UnBind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

