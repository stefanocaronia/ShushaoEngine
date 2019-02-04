#include <iostream>
#include <string>
#include <chrono>

#include "cycle.h"
#include "input.h"
#include "setime.h"
#include "system.h"
#include "glmanager.h"
#include "scenemanager.h"
#include "resources.h"
#include "config.h"
#include "debug.h"
#include "physics.h"
#include "design.h"

ShushaoEngine::Cycle* GAME;

namespace ShushaoEngine {

	using namespace std;

	Cycle::Cycle(string n) {
		name = n;
		GAME = this;
	}

	Cycle::~Cycle() {
		Debug::Log << "Cycle Destructor: " << endl;
	}

	bool Cycle::init() {

		for (bool& k : keys) k = false;

		GLManager::WIDTH = Config::displayWidth;
		GLManager::HEIGHT = Config::displayHeight;
		GLManager::fullscreen = Config::fullscreen;
		GLManager::Init(name, false);

		if (Config::Physics::enabled)
			Physics::init();

		Input::init();
		System::init();

		Awake();

		return true;
	}

	void Cycle::run() {

		if (!SceneManager::activeSceneSet)
			return;

		SceneManager::activeScene->ScanActiveComponentsInScene();
		SceneManager::activeScene->run(Cycle::INIT); // vengono chiamati gli Awake di tutti gli oggetti attivi

		Camera* activeCamera = SceneManager::activeScene->activeCamera;

		GLManager::SetFullscreen(Config::fullscreen);
		GLManager::Clear(activeCamera->backgroundColor.r, activeCamera->backgroundColor.g, activeCamera->backgroundColor.b, 1.0f, 1.0f);

		Start();

		// MAIN LOOP
		while (RUNNING) {

			Time::Update();

			SceneManager::activeScene->ScanActiveComponentsInScene();

			Input::update();
			Input();

			System::update();
			update();

			if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
				fixed();
			}

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
		if (Physics::enabled && Physics::debug) Physics::world->DrawDebugData();
		Design::ProcessDrawCalls();
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
		if (Physics::enabled) Physics::update();
		SceneManager::activeScene->run(Cycle::FIXED);
		FixedUpdate();
		Time::inFixedTimeStep = false;
	}

	void Cycle::exit() {
		End();
		SceneManager::activeScene->run(Cycle::EXIT);
		Input::exit();
		System::exit();
		Physics::exit();
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
