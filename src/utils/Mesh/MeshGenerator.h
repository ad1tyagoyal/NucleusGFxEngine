#pragma once
#include <iostream>
#include "src/utils/Mesh/Mesh.h"

namespace OpenGLEngine {

	class MeshGenerator {
	public:
		MeshGenerator();
		~MeshGenerator();

		static void GenerateMesh(Mesh* mesh, int width, int length, int levelOfDetail, float scale, int octaves,
			float lacunarity, float persistancy, bool randomizeMesh);
	};
}



//length, width = 256
//level of Detail = 0 - 6
