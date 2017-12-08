#include "input.h"
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

ShushaoEngine::Cycle* GAME;

namespace ShushaoEngine {

	using namespace std;

	Cycle::Cycle(string n) {
		name = n;
		GAME = this;
	}

	Cycle::~Cycle() {
		Debug::Log << "Cycle Destructor: " << endl;
		// SceneManager::Clear();
		// Resources::Clear();
		// System::Clear();
	}

	bool Cycle::init() {

		for (bool& k : keys) k = false;

		GLManager::WIDTH = Config::displayWidth;
		GLManager::HEIGHT = Config::displayHeight;
		GLManager::fullscreen = Config::fullscreen;
		GLManager::Init(name, false);

		Input::init();

		System::init();

		// here must be loaded the active scene
		Awake();

		return true;
	}

	void Cycle::run() {

		if (!SceneManager::activeSceneSet)
			return;

		SceneManager::activeScene->ScanActiveComponentsInScene();
		SceneManager::activeScene->run(Cycle::INIT);

		Camera* activeCamera = SceneManager::activeScene->activeCamera;

		GLManager::SetFullscreen(Config::fullscreen);
		GLManager::Clear(activeCamera->backgroundColor.r, activeCamera->backgroundColor.g, activeCamera->backgroundColor.b, 1.0f, 1.0f);

		Start();

		// MAIN LOOP
		while (RUNNING) {

			Time::Update();

			Input::update();
			Input();

			System::update();

			SceneManager::activeScene->ScanActiveComponentsInScene();

			if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
				fixed();
			}

			update();

			if (Time::renderDeltaTime >= Time::frameLimitDuration) {
				render();
			}
		}

		exit();
	}

	void Cycle::stop() {
		RUNNING = false;
	}

	void Cycle::render() {
		Time::renderTime = Time::GetTime();
		GLManager::Reset();
		SceneManager::activeScene->run(Cycle::RENDER);
		Render();
		Time::frameCount++;
		GLManager::Swap();
	}

	void Cycle::update() {
		Time::realtimeSinceStartup = Time::GetTime();
		SceneManager::activeScene->run(Cycle::UPDATE);
		Update();
	}

	void Cycle::fixed() {
		Time::fixedTime = Time::GetTime();
		Time::inFixedTimeStep = true;
		SceneManager::activeScene->run(Cycle::FIXED);
		FixedUpdate();
		Time::inFixedTimeStep = false;
	}

	void Cycle::exit() {
		End();
		SceneManager::activeScene->run(Cycle::EXIT);
		Input::exit();
		System::exit();
		SceneManager::Clear();
		Resources::Clear();
		System::Clear();
		GLManager::Quit();
	}

	string Cycle::INIT = "init";
	string Cycle::UPDATE = "update";
	string Cycle::FIXED = "fixed";
	string Cycle::RENDER = "render";
	string Cycle::EXIT = "exit";
}
