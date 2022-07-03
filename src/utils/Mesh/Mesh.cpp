#include "Mesh.h"
#include <iostream>
#include "src/utils/VertexBufferLayout.h"

namespace OpenGLEngine {
	Mesh::Mesh() {
	}

	void Mesh::SetData(std::vector<float> vertices, std::vector<unsigned int> indices) {
		m_VerticesData = vertices;
		m_Indices = indices;
	}

	Mesh::~Mesh() {
		delete &m_VAO;
		delete &m_VBO;
		delete &m_IBO;
	}

	void Mesh::BindMesh() {
		m_VAO->Bind();
		m_VBO->Bind();
		m_IBO->Bind();
	}

	void Mesh::InitComponents() {
		VertexBufferLayout layout;
		layout.Push<float>(3, "Position");
		//layout.Push<float>(3, "Normal");
		layout.Push<float>(2, "Texture Coordinate");

		m_VAO.reset(new VertexArray());
		m_VAO->Bind();

		m_VBO.reset(new VertexBuffer(m_VerticesData.size() * sizeof(float), &m_VerticesData[0]));
		m_VBO->SetLayout(layout);
		m_VBO->Bind();
		m_VAO->AddVertexBuffer(m_VBO);
		
		m_IBO.reset(new IndexBuffer(m_Indices.size(), &m_Indices.at(0)));
		m_IBO->Bind();
		m_VAO->SetIndexBuffer(m_IBO);

		//m_VAO->UnBind();
		//m_VBO->UnBind();
		//m_IBO->UnBind();
	}

}

