#include "cycle.h"
#include "setime.h"
#include "system.h"
#include "glmanager.h"
#include "scenemanager.h"
#include "resources.h"
#include "config.h"
#include "debug.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

namespace ShushaoEngine {

	Cycle::Cycle(string n) {
		name = n;
	}

	Cycle::~Cycle() {
		LOG("Cycle Destructor");

		SceneManager::Clear();
		Resources::Clear();
		System::Clear();
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
		SceneManager::activeScene->run(Cycle::INIT);

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

			SceneManager::activeScene->run(Cycle::UPDATE);
			update();

			if (Time::renderDeltaTime >= Time::frameLimitDuration) {
				render();
			}
		}

		exit();
	}

	void Cycle::render() {
		Time::renderTime = Time::GetTime();

		GLManager::Reset();
		GLManager::View = SceneManager::activeScene->activeCamera->getViewMatrix();

		SceneManager::activeScene->run(Cycle::RENDER);

		Render();

		Time::frameCount++;

		GLManager::Swap();
	}

	void Cycle::update() {
		Time::realtimeSinceStartup = Time::GetTime();
		Update();
	}

	void Cycle::fixed() {
		Time::fixedTime = Time::GetTime();
		Time::inFixedTimeStep = true;
		FixedUpdate();
		Time::inFixedTimeStep = false;
	}

	void Cycle::exit() {
		LOG("IN CYCLE EXIT");
		End();
		SceneManager::activeScene->run(Cycle::EXIT);
		System::exit();
		GLManager::Quit();
	}

	string Cycle::INIT = "init";
	string Cycle::UPDATE = "update";
	string Cycle::FIXED = "fixed";
	string Cycle::RENDER = "render";
	string Cycle::EXIT = "exit";
}
