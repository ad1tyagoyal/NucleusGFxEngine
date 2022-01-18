#pragma once
#include "src/interface/IApplication.h"
#include "src/utils/MeshGenerator.h"
#include "src/utils/Shader.h"
#include "src/utils/OpenGLWindow.h"

class RandomMeshGeneration : public IApplication {
public:
	RandomMeshGeneration(int width, int length, int levelOfDetail, float scale, int octaves,
		float lacunarity, float persistancy);
	~RandomMeshGeneration();

	virtual void OnUpdate() override;
private:
	MeshGenerator* m_MeshGenerator;
	//Shader* m_MeshShader;
	OpenGLWindow* m_Window;
};

