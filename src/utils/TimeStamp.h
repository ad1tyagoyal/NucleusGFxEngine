#pragma once

#include <GLFW/glfw3.h>

namespace OpenGLEngine {
	class TimeStamp {
	public:
		static void SceneStart();
		static void SceneEnd();
		
		inline static float GetDeltaTime() { return deltaTime; }
	private:
		static float deltaTime;
		static float sceneBeginTime;
		static float sceneEndTime;
	};

}


