#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"

namespace OpenGLEngine {

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray() {

	}

	void VertexArray::Bind() {
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::UnBind() {
		glBindVertexArray(0);
	}

	void const VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) {
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		const VertexBufferLayout& layout = vertexBuffer->GetLayout();
		const std::vector<VertexBufferLayoutElement>& elements = layout.GetElements();

		unsigned int offset = 0;
		for (int i = 0; i < elements.size(); i++) {
			//for each attribute
			const VertexBufferLayoutElement& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.Count,
				element.Type,
				element.Normalize,
				layout.GetStride(),
				(void*)offset);
			offset += element.Count * VertexBufferLayoutElement::GetSizeOfType(element.Type);
		}
		m_VertexBuffer = vertexBuffer;
	}

	void VertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& buffer) {
		glBindVertexArray(m_RendererID);
		buffer->Bind();
		m_IndexBuffer = buffer;
	}
}