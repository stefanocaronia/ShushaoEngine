#include "utility.h"
#include "setime.h"

#include <chrono>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>

namespace ShushaoEngine {

	using namespace std;
	using namespace std::chrono;

	float Time::GetTime() {
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
		realtimeSinceStartup = GetTime();
		deltaTime = realtimeSinceStartup - time;
		time = realtimeSinceStartup;
		fixedDeltaTime = realtimeSinceStartup - fixedTime;
		renderDeltaTime = realtimeSinceStartup - renderTime;
	}

	string Time::Clock() {

		int mil = duration_cast<milliseconds>(high_resolution_clock::now() - startTime).count();

		int mills = (int) (mil % 1000) ;
		int seconds = (int) (mil / 1000) % 60 ;
		int minutes = (int) ((mil / (1000*60)) % 60);
		//int hours   = (int) ((mil / (1000*60*60)) % 24);

		ostringstream clock;

		// clock << Utility::zerofill(hours, 2) << ":" << Utility::zerofill(minutes, 2) << ":" << Utility::zerofill(seconds, 2)<< "." << Utility::zerofill(mills, 3);
		clock <<util::zerofill(minutes, 2) << ":" << util::zerofill(seconds, 2)<< "." << util::zerofill(mills, 3);

		return clock.str();
	}

	// static members definitions
	float Time::deltaTime = 0.0f;
	float Time::fixedDeltaTime = 0.0f;
	float Time::renderDeltaTime = 0.0f;
	float Time::fixedTime = 0.0f;
	float Time::frameCount = 0.0f;
	float Time::fixedRateLimit = 60.0f;
	float Time::fixedLimitDuration = 1.0f / 60.0f;
	float Time::frameLimitDuration = 0.0f;
	float Time::frameRateLimit = 0.0f;
	float Time::renderTime = 0.0f;
	float Time::time = 0.0f;
	float Time::realtimeSinceStartup = 0.0f;
	bool Time::inFixedTimeStep = false;
	system_clock::time_point Time::startTime = high_resolution_clock::now();
}
