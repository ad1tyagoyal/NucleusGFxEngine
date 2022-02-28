#pragma once
namespace OpenGLEngine {
	class Cube {
	public:
		Cube() {}
		~Cube() {}
		
		inline float* GetVertices() { return m_Vertices; }
		inline unsigned int* GetIndices() { return m_Indices; }
		
		inline unsigned int GetSizeOfBuffer() { return sizeof(m_Vertices); }
		inline unsigned int GetCountOfIndices() { return sizeof(m_Indices) / sizeof(unsigned int); }
		

	private:
		float m_Vertices[24] = {
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f, -2.0f,
			-1.0f,  1.0f, -2.0f,
			 1.0f,  1.0f, -2.0f,
			 1.0f, -1.0f, -2.0f
		};

		unsigned int m_Indices[36] = {
			//front
			0, 1, 2, 2, 3, 0,
			//back
			7, 6, 5, 5, 4, 7,
			//right
			4, 5, 1, 1, 0, 4,
			//left
			3, 2, 6, 6, 7, 3,
			//top
			1, 5, 6, 6, 2, 1,
			//bottom
			3, 7, 4, 4, 0, 3
		};

	};
}




