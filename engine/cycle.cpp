#include <iostream>
#include <string>
#include <chrono>

#include "cycle.h"
#include "input.h"
#include "stime.h"
#include "system.h"
#include "glmanager.h"
#include "scenemanager.h"
#include "resources.h"
#include "config.h"
#include "debug.h"
#include "physics/physics.h"
#include "design.h"

se::Cycle* GAME;

namespace se {

	using namespace std;

	Cycle::Cycle(string name_) {
		name = name_;
		GAME = this;
	}

	Cycle::~Cycle() {
		Debug::Log << "Cycle Destructor" << endl;
	}

	bool Cycle::init() {

		for (bool& k : keys) {
            k = false;
		}

		GLManager::WIDTH = Config::displayWidth;
		GLManager::HEIGHT = Config::displayHeight;
		GLManager::fullscreen = Config::fullscreen;
		GLManager::Init(name, false);

		if (Config::Physics::enabled) {
			Physics::init();
		}

		Input::init();
		System::init();

		Awake();

		return true;
	}

	void Cycle::run() {

		if (!SceneManager::activeSceneSet)
			return;

		SceneManager::activeScene->ScanActiveComponents();
		SceneManager::activeScene->ScanActiveLights();
		SceneManager::activeScene->run(Cycle::Stage::INIT); // vengono chiamati qui gli Awake di tutti gli oggetti attivi

		if (Debug::enabled) {
			SceneManager::activeScene->PrintHierarchy();
			SceneManager::activeScene->PrintActiveComponentsInScene();
			SceneManager::activeScene->PrintActiveRenderersInScene();
			SceneManager::activeScene->PrintActiveLightsInScene();
			System::ListServices();
			SceneManager::activeScene->activeCamera->print();
			Resources::toString();
			Config::Layers.toString("Layers");
			Config::SortingLayers.toString("SortingLayers");
		}

		Camera* activeCamera = SceneManager::activeScene->activeCamera;

		GLManager::SetFullscreen(Config::fullscreen);
		GLManager::Clear(activeCamera->backgroundColor.r, activeCamera->backgroundColor.g, activeCamera->backgroundColor.b, 1.0f, 1.0f);

		Start();

		// MAIN LOOP
		while (RUNNING) {

			Time::Update();

			SceneManager::activeScene->ScanActiveComponents();
			SceneManager::activeScene->ScanActiveLights();

			Input::update();
			GetInput();

			System::update();
			update();

			if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
				fixed();
			}

			if (Time::renderDeltaTime >= Time::frameLimitDuration) {
				render();
			}

			SceneManager::activeScene->componentsScanned = false;
		}

		exit();
	}

	void Cycle::stop() {
		RUNNING = false;
	}

	void Cycle::render() {
		Time::renderTime = Time::GetTime();
		GLManager::Reset();
		SceneManager::activeScene->run(Cycle::Stage::RENDER);
		Render();
		if (Physics::enabled && Physics::debug) Physics::world->DrawDebugData();
		SceneManager::activeScene->renderOverlay();
		Time::frameCount++;
		GLManager::Swap();
	}

	void Cycle::update() {
		Time::realtimeSinceStartup = Time::GetTime();
		GLManager::Update();
		SceneManager::activeScene->run(Cycle::Stage::UPDATE);
		Update();
	}

	void Cycle::fixed() {
		Time::fixedTime = Time::GetTime();
		Time::inFixedTimeStep = true;
		if (Physics::enabled) Physics::update();
		SceneManager::activeScene->run(Cycle::Stage::FIXED);
		FixedUpdate();
		Time::inFixedTimeStep = false;
	}

	void Cycle::exit() {
		End();
		SceneManager::activeScene->run(Cycle::Stage::EXIT);
		Input::exit();
		System::exit();
		Physics::exit();
		SceneManager::Clear();
		Resources::Clear();
		System::Clear();
		GLManager::Quit();
	}
}
