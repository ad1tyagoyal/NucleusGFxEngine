#include "TimeStamp.h"

namespace OpenGLEngine {

	float TimeStamp::deltaTime = 0.0f;
	float TimeStamp::sceneBeginTime = 0.0f;
	float TimeStamp::sceneEndTime = 0.0f;

	void TimeStamp::SceneStart() {
		sceneBeginTime = (float)glfwGetTime();
	}
	void TimeStamp::SceneEnd() {
		sceneEndTime = (float)glfwGetTime();
		deltaTime = sceneEndTime - sceneBeginTime;
	}
}
