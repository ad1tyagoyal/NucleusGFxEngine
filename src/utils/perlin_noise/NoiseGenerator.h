#pragma once
#include <iostream>
#include <vector>

#include "glm/vec2.hpp"

class NoiseGenerator {
public:
	static std::vector<float> GenerateNoise(int width, int height, float scale,int octaves, 
														float lacunarity, float persistancy, glm::vec2 offset);
};

