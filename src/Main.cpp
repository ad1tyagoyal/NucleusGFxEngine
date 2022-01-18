#include <iostream>

#include "src/projects/OpenGLEngine/OpenGLEngine.h"

int main() {
	
	OpenGLEngine* engine = new OpenGLEngine();
	engine->OnUpdate();
	return 0;
}