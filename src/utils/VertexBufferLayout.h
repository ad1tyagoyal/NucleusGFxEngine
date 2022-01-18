#pragma once
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>



struct VertexBufferLayoutElement {
	std::string Name;
	unsigned int Type;
	int Count;
	unsigned char Normalize;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 4;
		}
		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template <typename T>
	void Push(int count, const std::string& name) {
		static_assert(false);
	}

	template <>
	void Push<float>(int count, const std::string& name) {
		m_Elements.push_back({ name, GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(int count, const std::string& name) {
		m_Elements.push_back({ name, GL_UNSIGNED_INT, count, GL_TRUE });
		m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(int count, const std::string& name) {
		m_Elements.push_back({ name, GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_Stride += count * VertexBufferLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const unsigned int GetStride() const { return m_Stride; }
	inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return m_Elements; }

private:
	std::vector<VertexBufferLayoutElement> m_Elements;
	unsigned int m_Stride;
};

