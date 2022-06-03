#pragma once
#include "Buffer.h"
#include "VertexBufferLayout.h"
#include <memory>


namespace OpenGLEngine {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void UnBind();

		void const AddVertexBuffer(std::shared_ptr<VertexBuffer>& buffer);
		void SetIndexBuffer(std::shared_ptr<IndexBuffer>& buffer);

		inline std::shared_ptr<IndexBuffer>& GetIndexBuffer() { return m_IndexBuffer; }
		inline std::shared_ptr<VertexBuffer>& GetVertexBuffer() { return m_VertexBuffer; }

	private:
		unsigned int m_RendererID;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}