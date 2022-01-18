#pragma once
#include"src/utils/VertexBufferLayout.h"

class VertexBuffer {
public:
	//template<typename T>
	VertexBuffer(unsigned int size, float* vertices);
	~VertexBuffer();

	void Bind();
	void UnBind();

	inline VertexBufferLayout& GetLayout() { return m_Layout; }
	inline void SetLayout(const VertexBufferLayout& layout) { m_Layout = layout; }


private:
	unsigned int m_RendererID;
	VertexBufferLayout m_Layout;
};

class IndexBuffer {

public:
	IndexBuffer(unsigned int count, unsigned int* indices);
	~IndexBuffer();

	void Bind();
	void UnBind();

	inline unsigned int GetCount() { return m_Count; }

private:
	unsigned int m_RendererID;
	unsigned int m_Count = 0;
};


