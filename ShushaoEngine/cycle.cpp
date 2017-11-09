#include "cycle.h"
#include "setime.h"
#include "system.h"
#include "glmanager.h"
#include "scenemanager.h"
#include "resources.h"
#include "config.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

namespace ShushaoEngine {

	Cycle::Cycle(string n) {
		name = n;
	}

	Cycle::~Cycle() {
		// to do
	}

	void Cycle::init() {

		for (bool& k : keys) k = false;

		GLManager::WIDTH = Config::displayWidth;
		GLManager::HEIGHT = Config::displayHeight;
		GLManager::Fullscreen = Config::Fullscreen;
		GLManager::Init(name, false);

		System::init();

		Awake();
	}

	void Cycle::run() {

		SceneManager::activeScene->ScanActiveComponentsInScene();
		SceneManager::activeScene->run(INIT);

		GLManager::SetFullscreen(Config::Fullscreen);
		GLManager::Clear(SceneManager::activeScene->activeCamera->backgroundColor.r, SceneManager::activeScene->activeCamera->backgroundColor.g, SceneManager::activeScene->activeCamera->backgroundColor.b, 1.0f, 1.0f);
		GLManager::Projection = SceneManager::activeScene->activeCamera->getProjectionMatrix();
		GLManager::View = SceneManager::activeScene->activeCamera->getViewMatrix();

		Start();

		// MAIN LOOP
		while (RUNNING) {

			Time::Update();

			SceneManager::activeScene->ScanActiveComponentsInScene();

			System::update();

			Input();

			if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
				fixed();
			}

			SceneManager::activeScene->run(UPDATE);
			update();

			if (Time::renderDeltaTime >= Time::frameLimitDuration) {
				render();
			}
		}

		End();
		exit();
	}

	void Cycle::render() {
		Time::renderTime = Time::getTime();

		GLManager::Reset();
		GLManager::View = SceneManager::activeScene->activeCamera->getViewMatrix();

		SceneManager::activeScene->run(RENDER);

		Render();

		Time::frameCount++;

		GLManager::Swap();
	}

	void Cycle::update() {
		Time::realtimeSinceStartup = Time::getTime();
		Update();
	}

	void Cycle::fixed() {
		Time::fixedTime = Time::getTime();
		Time::inFixedTimeStep = true;
		FixedUpdate();
		Time::inFixedTimeStep = false;
	}

	void Cycle::exit() {
		SceneManager::activeScene->run(EXIT);
		Resources::Clean();
		System::exit();
		GLManager::Quit();
		End();
	}
}
