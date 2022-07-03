#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/utils/Buffer.h"
#include "src/utils/VertexArray.h"

#include "src/utils/Shader.h"

#include "src/utils/OpenGLWindow.h"

//Mesh - vertices, triangles, UVs
//Vertex - position, texture coordinates, normals (for calculating lighting)

namespace OpenGLEngine {

	struct Vertex {
		glm::vec3 Position;
		//glm::vec3 Normal;
		glm::vec2 TextCoordinate;
	};

	struct MeshTexture {
		unsigned int id;
		std::string type;
	};

	class Mesh {
	public:
		Mesh();
		~Mesh();
		void BindMesh();
		inline std::shared_ptr<VertexArray> GetVertexArray() { return m_VAO; }
		void SetData(std::vector<float> vertices, std::vector<unsigned int> indices);
		void InitComponents();


	private:

		std::vector<float> m_VerticesData;
		std::vector<unsigned int> m_Indices;
		//std::vector<Texture> m_Textures;

		std::shared_ptr<VertexArray> m_VAO;
		std::shared_ptr<VertexBuffer> m_VBO;
		std::shared_ptr<IndexBuffer> m_IBO;
	};
}



