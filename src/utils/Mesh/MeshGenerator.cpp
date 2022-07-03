#include "MeshGenerator.h"

#include <vector>
#include "src/utils/perlin_noise/SimplexNoise.h"
#include "src/utils/perlin_noise/NoiseGenerator.h"

namespace OpenGLEngine {

	MeshGenerator::MeshGenerator() {}

	MeshGenerator::~MeshGenerator() {
	}

	void MeshGenerator::GenerateMesh(Mesh* mesh, int width, int length, int levelOfDetail, float scale, int octaves,
		float lacunarity, float persistancy, bool randomizeMesh) {
		
		std::vector<float> noiseValues;
		if(randomizeMesh)
			noiseValues = NoiseGenerator::GenerateNoise(width, length, scale, octaves, lacunarity, persistancy, { 1.45f, 3.56f });
		else {
			int n = width * length;
			for (int i = 0; i < n; i++)
				noiseValues.push_back(0);
		}
		
		
		//int meshSimplificationIncrement = (levelOfDetail == 0) ? 1 : (2 * levelOfDetail);
		//int verticesPerLine = ((width - 1) / levelOfDetail) + 1;

		std::vector<float> verticesData;
		std::vector<unsigned int> indices;

		for (int vertexIndex = 0, x = 0; x < width; x ++) {
			for (int y = 0; y < length; y ++) {
				//vertices.push_back({ glm::vec3(x, noiseValues[vertexIndex], y),
				//					 /*glm::vec3(0.0f, 0.0f, 0.0f),*/
				//					 glm::vec2(x/(float)width, y/(float)length) });

				//positions
				verticesData.push_back(x);
				verticesData.push_back(noiseValues[vertexIndex]);
				verticesData.push_back(y);
				//UV
				verticesData.push_back(x / (float)10);
				verticesData.push_back(y / (float)10);

				if (x < width - 1 && y < length - 1) {
					indices.push_back(vertexIndex);
					indices.push_back(vertexIndex + width + 1);
					indices.push_back(vertexIndex + width);

					indices.push_back(vertexIndex + width + 1);
					indices.push_back(vertexIndex);
					indices.push_back(vertexIndex + 1);
				}
				vertexIndex++;
			}
		}

		mesh->SetData(verticesData, indices);
	}

	
}

