#include "cycle.h"
#include "setime.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

namespace ShushaoEngine {

	bool Cycle::init() {

		for (bool& k : keys) {
			k = false;
		}

		Awake();

		return READY;
	}

	void Cycle::run() {

		if (!READY) {
			cout << "NON READY" << endl;
			RUNNING = false;
			return;
		}

		if (RUNNING) {
			Start();
		}

		// MAIN LOOP
		while (RUNNING) {

			Time::Update();

			Input();

			if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
				fixedUpdateCycle();
			}

			updateCycle();

			if (Time::renderDeltaTime >= Time::frameLimitDuration) {
				renderCycle();
			}
		}

		End();
	}

	void Cycle::renderCycle() {
		Time::renderTime = Time::getTime();
		Render();
		Time::frameCount++;
	}

	void Cycle::updateCycle() {
		Time::realtimeSinceStartup = Time::getTime();
		Update();
	}

	void Cycle::fixedUpdateCycle() {
		Time::fixedTime = Time::getTime();
		Time::inFixedTimeStep = true;
		FixedUpdate();
		Time::inFixedTimeStep = false;
	}

	void Cycle::exit() {
		End();
	}
}
