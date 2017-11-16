#include <iostream>

#include "libs.h"
#include "debug.h"
#include "game.h"
#include "scenemanager.h"
#include "spriterenderer.h"
#include "resources.h"
#include "shader.h"
#include "texture.h"

#include "setime.h"
#include "level.h"
#include "system.h"


using namespace std;
using namespace glm;
using namespace ShushaoEngine;

Game::Game(string title) : Cycle(title) {

  	Time::setFrameRateLimit(120.0f);
	Time::setFixedRateLimit(60.0f);

	Config::displayWidth = 1024;
	Config::displayHeight = Config::displayWidth / (16.0f/9.0f);
	Config::pixelPerUnit = 16;

	Config::Layers[1] = "Player";
	Config::Layers[2] = "Objects";

	Config::SortingLayers[1] = "Background";
	Config::SortingLayers[2] = "Characters";

	Debug::Enabled = true;
	Debug::DebugGridMode = GridMode::ORTHOGRAFIC;
}

Game::~Game() {
   // do
}

void Game::Awake() {

	Resources::Load<Texture>("assets/pancrazio.png");
	Resources::Load<Texture>("assets/night.jpg");
	Resources::Load<Texture>("assets/pancsmile.png");
	Resources::Load<Shader>("shaders/standard");

	//GameData::PrintAllObjects();

	SceneManager::LoadScene<Level>("Level 1");

	Camera* camera = SceneManager::activeScene->activeCamera;
	camera->backgroundColor = {0.2f, 0.2f, 0.8f, 1.0f};
	camera->setOrthographic(true);
	camera->setNearClipPlane(12.0f);
	camera->setFarClipPlane(1.0f);
	camera->setOrthographicSize(5.0f);

	camera->transform->position = vec3(0.0f, 0.0f, 10.0f);
	camera->transform->rotation = quat(0.0f, 0.0f, 0.0f, 0.0f);
	camera->transform->up = vec3(0.0f, 1.0f, 0.0f);

	SceneManager::activeScene->PrintHierarchy();
	SceneManager::activeScene->PrintActiveComponentsInScene();
	SceneManager::activeScene->PrintActiveRenderersInScene();
	System::ListServices();
	camera->print();


}

void Game::Start() {


}

void Game::Update() {

}

void Game::Render() {

}

void Game::FixedUpdate() {

}

void Game::End() {

}

void Game::Input() {

	SDL_Event ev;
	SDL_Keycode scancode;

	while (SDL_PollEvent(&ev) != 0) {
		switch (ev.type) {
		case SDL_QUIT:
			RUNNING = false;
			break;
		case SDL_KEYDOWN:
			scancode = ev.key.keysym.scancode;
			if (!keys[scancode])
				keys[scancode] = true;
			break;
		case SDL_KEYUP:
			scancode = ev.key.keysym.scancode;
			keys[scancode] = false;
			break;
		case SDL_JOYAXISMOTION:
			cout << ev.jaxis.which << " " << ev.jaxis.axis << " " << ev.jaxis.value << endl;
			break;
		case SDL_JOYBUTTONDOWN:
			if (ev.jbutton.button == 0)
				RUNNING = false;
			break;
		}
	}

	if ((keys[SDL_SCANCODE_LCTRL] && keys[SDL_SCANCODE_Q]) || keys[SDL_SCANCODE_ESCAPE])
		RUNNING = false;

	// WINDOW
	if (keys[SDL_SCANCODE_F11]) {
		keys[SDL_SCANCODE_F11] = false;

		GLManager::ToggleFullscreen();
		SDL_Delay(100);
	}
}
