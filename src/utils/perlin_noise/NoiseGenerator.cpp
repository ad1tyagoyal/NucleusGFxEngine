#include "NoiseGenerator.h"
#include "src/utils/perlin_noise/SimplexNoise.h"


std::vector<float> NoiseGenerator::GenerateNoise(int width, int height, float scale, int octaves, 
								float lacunarity, float persistancy, glm::vec2 offset) {
	/*glm::vec2* octavesOffset = new glm::vec2[octaves];
	
	for (int min = -100000, max = 100000, i = 0; i < octaves; i++) {
		float xOffset = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + offset.x;
		float yOffset = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + offset.y;
		octavesOffset[i] = { xOffset, yOffset };
	}*/

	std::vector<float> noiseValues;

	for (int vertexIndex = 0 ,x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			float amplitude = 1.0f;
			float frequency = 1.0f;
			float noiseHeight = 0.0f;
			
			for (int i = 0; i < octaves; i++) {
				float xSample = (float)x / (float) width * scale * frequency /*+ octavesOffset[i].x*/;
				float ySample = (float)y / (float) height * scale * frequency /*+ octavesOffset[i].y*/;
				float noiseValue = SimplexNoise::noise(xSample, ySample);
				noiseHeight += noiseValue * amplitude;
				
				amplitude *= persistancy;
				frequency *= lacunarity;
			}
			noiseValues.push_back(noiseHeight);
			vertexIndex++;
		}
	}
	return noiseValues;
}
