#include "libs.h"
#include "glmanager.h"
#include "spriterenderer.h"
#include "sprite.h"
#include "transform.h"
#include "shader.h"

#include <SDL.h>

#include <glm.hpp>
#include <iostream>

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	bool GLManager::Init(string title, bool fs) {

		Fullscreen = fs;

		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		SDL_JoystickEventState(SDL_ENABLE);
		Joystick = SDL_JoystickOpen(0);

		SDL_GL_SetSwapInterval(1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);
		DESKTOP_WIDTH = dm.w;
		DESKTOP_HEIGHT = dm.h;

		if (Fullscreen) {
			gWindow = SDL_CreateWindow(title.c_str(), 0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
		} else {
			gWindow = SDL_CreateWindow(title.c_str(), DESKTOP_WIDTH / 2 - WIDTH / 2, DESKTOP_HEIGHT / 2 - HEIGHT / 2, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		gContext = SDL_GL_CreateContext(gWindow);
		SDL_GL_MakeCurrent(gWindow, gContext);

		// Init GLEW
		glewExperimental = GL_TRUE;
		glewInit();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_MULTISAMPLE);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);

		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;

	}

	void GLManager::Quit() {
		SDL_JoystickClose(Joystick);
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		SDL_GL_DeleteContext(gContext);
		SDL_Quit();
	}

	void GLManager::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0f);
	}

	void GLManager::Clear(float r, float g, float b, float a, float depth = 1.0f) {
		glClearColor(r, g, b, a);
		glClearDepth(depth);
	}

	void GLManager::SetFullscreen(bool fs) {
		Fullscreen = fs;
		if (Fullscreen) {
			SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			glViewport(0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT);
		} else {
			SDL_SetWindowFullscreen(gWindow, SDL_FALSE);
			glViewport(0, 0, WIDTH, HEIGHT);
		}
	}

	void GLManager::ToggleFullscreen() {
		SetFullscreen(!Fullscreen);
	}

	void GLManager::Swap() {
		SDL_GL_SwapWindow(gWindow);
	}

	void GLManager::Reset() {
		Clear();
		glLoadIdentity();
	}


	// inizialize static properties

	SDL_GLContext GLManager::gContext;
	SDL_Window* GLManager::gWindow;
	SDL_Renderer* GLManager::gRenderer;
	SDL_Joystick* GLManager::Joystick;
	mat4 GLManager::Projection;
	mat4 GLManager::View;
	bool GLManager::Fullscreen = false;

	unsigned int GLManager::DESKTOP_WIDTH;
	unsigned int GLManager::DESKTOP_HEIGHT;
	unsigned int GLManager::WIDTH;
	unsigned int GLManager::HEIGHT;
}



