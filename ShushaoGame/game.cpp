#include <iostream>

#include "libs.h"
#include "game.h"
#include "scenemanager.h"
#include "resources.h"
#include "shader.h"
#include "texture.h"

#include "setime.h"
#include "level.h"


using namespace std;
using namespace glm;

Game::Game(string title) : Cycle(title) {

  	Time::setFrameRateLimit(120.0f);
	Time::setFixedRateLimit(20.0f);

	// Config::displayWidth = 600;
	// Config::displayHeight = (int)(Config::displayWidth / Config::displayAspect);

	Config::Layers[1] = "Player";
	Config::Layers[2] = "Background";
}

Game::~Game() {
   // do
}

void Game::Awake() {

	Resources::Load<Texture>("assets/pancrazio.png");
	Resources::Load<Texture>("assets/pancsmile.png");
	Resources::Load<Shader>("shaders/standard");
	Resources::Load<Shader>("shaders/standard", "shader2");


	//GameData::PrintAllObjects();

	SceneManager::LoadScene<Level>();

	SceneManager::activeScene->activeCamera->backgroundColor = {0.2f, 0.2f, 0.8f, 1.0f};
	SceneManager::activeScene->activeCamera->orthographic = true;
	SceneManager::activeScene->activeCamera->orthographicSize = 5.0f;
	SceneManager::activeScene->activeCamera->rect = {0.0f, 0.0f, 1.0f, 1.0f};

	SceneManager::activeScene->activeCamera->transform->position = vec3(0.0f, 0.0f, -4.0f);
	SceneManager::activeScene->activeCamera->transform->rotation = quat(0.0f, 0.0f, 0.0f, 0.0f);
	SceneManager::activeScene->activeCamera->transform->up = vec3(0.0f, 1.0f, 0.0f);

	//GameData::PrintAllObjects();
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
