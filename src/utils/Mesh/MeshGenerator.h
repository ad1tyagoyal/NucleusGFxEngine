#pragma once
#include <iostream>

#include "src/utils/Mesh.h"

class MeshGenerator {
public:
	MeshGenerator();
	MeshGenerator(int width, int length, int levelOfDetail, float scale, int octaves,
													float lacunarity, float persistancy);
	~MeshGenerator();

	inline Mesh* GetMesh() const { return m_Mesh; }

private:
	Mesh* m_Mesh;
};


//length, width = 256
//level of Detail = 0 - 6
