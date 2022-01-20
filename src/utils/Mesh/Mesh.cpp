#include "Mesh.h"
#include <iostream>
#include "src/utils/VertexBufferLayout.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices
								/*, std::vector<Texture>& textures*/) 
	: m_Vertices(vertices), m_Indices(indices)/*, m_Textures(textures)*/ {
	SetupMesh();
}

void Mesh::Draw() {
	m_VAO->Bind();
	m_VBO->Bind();
	m_IBO->Bind();
	m_MeshShader->Bind();
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::SetupMesh() {
	m_VAO = new VertexArray();
	m_VAO->Bind();
	m_VBO = new VertexBuffer(m_Vertices.size() * sizeof(Vertex), &m_Vertices.at(0).Position.x);
	m_VBO->Bind();
	m_IBO = new IndexBuffer(m_Indices.size() * sizeof(unsigned int), &m_Indices.at(0));
	m_IBO->Bind();
	m_MeshShader = new Shader("src/res/BAsicMeshShader.shader");
	VertexBufferLayout layout;
	layout.Push<float>(3, "Position");
	layout.Push<float>(3, "Normal");
	layout.Push<float>(2, "Texture Coordinate");

	m_VAO->AddVertexBuffer(*m_VBO, layout);
	m_VAO->UnBind();
}
