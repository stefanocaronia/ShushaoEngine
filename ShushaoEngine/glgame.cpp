#include <vector>

#include "glgame.h"
#include "gamedata.h"
#include "setime.h"
#include "glmanager.h"
#include "shaderprogram.h"
#include "maincamera.h"
#include "gameobject.h"
#include "scenemanager.h"

using namespace std;

namespace ShushaoEngine {

	GLGame::GLGame(string title) {

		TITLE = title;
	}
	GLGame::~GLGame() {

		//todo
	}

	bool GLGame::init() {

		GL.WIDTH = Config::displayWidth;
		GL.HEIGHT = Config::displayHeight;
		GL.Fullscreen = Config::Fullscreen;

		GL.Init(TITLE, false);

		return Cycle::init();
	}

	void GLGame::run() {

		if (Scenes.activeScene == nullptr || Scenes.activeScene->root == nullptr) {
			READY = false;
		} else {
			READY = true;
		}

		Scenes.activeScene->root->run(INIT);

		if (READY) {

			Camera* camera = Scenes.activeScene->activeCamera;

			GL.SetFullscreen(Config::Fullscreen);
			GL.Clear(camera->backgroundColor.r, camera->backgroundColor.g, camera->backgroundColor.b, 1.0f, 1.0f);
			GL.Projection = camera->getProjectionMatrix();
			GL.View = camera->getViewMatrix();
		}

		return Cycle::run();
	}

	void GLGame::fixedUpdateCycle() {

		Scenes.activeScene->root->run(FIXED_UPDATE);

		Cycle::fixedUpdateCycle();
	}

	void GLGame::updateCycle() {

		Scenes.activeScene->root->run(UPDATE);

		Cycle::updateCycle();
	}

	void GLGame::renderCycle() {
		Time::renderTime = Time::getTime();

		GL.Reset();
		GL.View = Scenes.activeScene->activeCamera->getViewMatrix();

		// Cycle::renderCycle();
		// invece di chiamare il metodo base lo riscrivo (per retrodatare il renderTime)

		Scenes.activeScene->root->run(RENDER);

		Render();

		Time::frameCount++;

		GL.Swap();
	}

	void GLGame::exit() {

		Scenes.activeScene->root->run(EXIT);

		GL.Quit();
		Cycle::exit();
	}



}