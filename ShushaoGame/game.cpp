#include <iostream>

#include "game.h"

#include "setime.h"
#include "level.h"


using namespace std;
using namespace glm;

Game::Game(string title) : GLGame(title) {
   // do
}

Game::~Game() {
   // do
}

void Game::Awake() {

	Scenes.LoadScene<Level>();

	Scenes.activeScene->activeCamera->backgroundColor = {0.2f, 0.2f, 0.8f, 1.0f};
	Scenes.activeScene->activeCamera->orthographic = true;
	Scenes.activeScene->activeCamera->orthographicSize = 5.0f;
	Scenes.activeScene->activeCamera->rect = {0.0f, 0.0f, 1.0f, 1.0f};

	Scenes.activeScene->activeCamera->transform->position = vec3(0.0f, 0.0f, -4.0f);
	Scenes.activeScene->activeCamera->transform->rotation = quat(0.0f, 0.0f, 0.0f, 0.0f);
	Scenes.activeScene->activeCamera->transform->up = vec3(0.0f, 1.0f, 0.0f);

	// GameData::PrintAllObjects();
}

void Game::Start() {

	//PlayerSR->init();
}

void Game::Update() {
	//Player.transform->updateCycle();

	//cout << Time::frameCount << endl;
}

void Game::Render() {
	//PlayerSR->renderCycle();

	//RUNNING = false;
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

		GL.ToggleFullscreen();
		SDL_Delay(100);
	}
}
