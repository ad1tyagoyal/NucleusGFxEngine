#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/utils/Buffer.h"
#include "src/utils/VertexArray.h"

#include "Shader.h"

#include "src/utils/OpenGLWindow.h"

//Mesh - vertices, triangles, UVs
//Vertex - position, texture coordinates, normals (for calculating lighting)

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextCoordinate;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices/*, std::vector<Texture>& textures*/);
	void Draw();

private:
	void SetupMesh();

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	//std::vector<Texture> m_Textures;

	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	IndexBuffer* m_IBO;
	Shader* m_MeshShader;
};

