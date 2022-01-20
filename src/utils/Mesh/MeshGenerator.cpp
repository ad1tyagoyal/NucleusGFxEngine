#include "MeshGenerator.h"

#include <vector>
#include "src/utils/perlin_noise/SimplexNoise.h"
#include "src/utils/perlin_noise/NoiseGenerator.h"


MeshGenerator::MeshGenerator() { }

MeshGenerator::MeshGenerator(int width, int length, int levelOfDetail, float scale, int octaves,
																float lacunarity, float persistancy) {

	std::vector<float> noiseValues = NoiseGenerator::GenerateNoise(width, length, scale, octaves, lacunarity, persistancy, { 1.45f, 3.56f });
	int meshSimplificationIncrement = (levelOfDetail == 0) ? 1 : (2 * levelOfDetail);
	int verticesPerLine = ((width - 1) / levelOfDetail) + 1;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (int vertexIndex = 0, x = 0; x < width; x += meshSimplificationIncrement) {
		for (int y = 0; y < length; y += meshSimplificationIncrement) {
			vertices.push_back({ glm::vec3(x, noiseValues[vertexIndex], y),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec2(0.0f, 0.0f) });
			
			if (x < width - 1 && y < length - 1) {
				indices.push_back(vertexIndex);
				indices.push_back(vertexIndex + verticesPerLine + 1);
				indices.push_back(vertexIndex + verticesPerLine);

				indices.push_back(vertexIndex + verticesPerLine + 1);
				indices.push_back(vertexIndex);
				indices.push_back(vertexIndex + 1);
			}
			vertexIndex++;
		}
	}

	m_Mesh = new Mesh(vertices, indices);
}

MeshGenerator::~MeshGenerator() {
}
