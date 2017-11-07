#include "setime.h"
#include <chrono>

namespace ShushaoEngine {

	using namespace std::chrono;

	float Time::getTime() {
		return (float) duration_cast<milliseconds>(high_resolution_clock::now() - startTime).count() / 1000.f;
	}

	void Time::setFrameRateLimit(float fr) {
		frameRateLimit = fr;
		frameLimitDuration = 1.f / frameRateLimit;
	}

	void Time::setFixedRateLimit(float fr) {
		fixedRateLimit = fr;
		fixedLimitDuration = 1.f / fixedRateLimit;
	}

	void Time::Update() {
		realtimeSinceStartup = getTime();
		deltaTime = realtimeSinceStartup - time;
		time = realtimeSinceStartup;
		fixedDeltaTime = realtimeSinceStartup - fixedTime;
		renderDeltaTime = realtimeSinceStartup - renderTime;
	}

	// static members definitions
	float Time::deltaTime = 0.0f;
	float Time::fixedDeltaTime = 0.0f;
	float Time::renderDeltaTime = 0.0f;
	float Time::fixedTime = 0.0f;
	float Time::frameCount = 0.0f;
	float Time::fixedRateLimit = 20.0f;
	float Time::fixedLimitDuration = 1.0f / 20.0f;
	float Time::frameLimitDuration = 0.0f;
	float Time::frameRateLimit = 0.0f;
	float Time::renderTime = 0.0f;
	float Time::time = 0.0f;
	float Time::realtimeSinceStartup = 0.0f;
	bool Time::inFixedTimeStep = false;
	system_clock::time_point Time::startTime = high_resolution_clock::now();
}
