#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#include "debug.h"
#include "glmanager.h"
#include "standardshader.h"
#include "wireframeshader.h"
#include "baseshader.h"
#include "fontshader.h"
#include "meshshader.h"

namespace se {

	using namespace std;

	bool GLManager::Init(std::string title, bool fs) {

		fullscreen = fs;

		SDL_Init(SDL_INIT_EVERYTHING); //  | SDL_INIT_JOYSTICK
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		// TTF_Init();

		FT_Init_FreeType(&lFreetype);

		Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		Mix_AllocateChannels(16);

        SDL_GL_SetSwapInterval(1);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm);
		DESKTOP_WIDTH = dm.w;
		DESKTOP_HEIGHT = dm.h;

		if (fullscreen) {
			gWindow = SDL_CreateWindow(title.c_str(), 0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
		} else {
			gWindow = SDL_CreateWindow(title.c_str(), DESKTOP_WIDTH / 2 - WIDTH / 2, DESKTOP_HEIGHT / 2 - HEIGHT / 2, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
		}

		//gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		gContext = SDL_GL_CreateContext(gWindow);
		SDL_GL_MakeCurrent(gWindow, gContext);

		// Init GLEW
		glewExperimental = GL_TRUE;
		glewInit();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		//glEnable(GL_MULTISAMPLE);
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		//glEnable(GL_LINE_SMOOTH);
		//glEnable(GL_POLYGON_SMOOTH);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Shader predefiniti
		AddShader(new StandardShader());
		AddShader(new BaseShader());
		AddShader(new WireframeShader());
		AddShader(new FontShader());
		AddShader(new MeshShader());

		ready = true;
		return true;
	}

	void GLManager::Quit() {

		//SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		SDL_GL_DeleteContext(gContext);
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();

		for (auto& it : shaders) {
			if (it.second != nullptr) {
				Debug::Log << "Cancello " << it.second->name  << endl; //<< " (" + util::classtitle(typeid(*it.second).name()) +")"
				delete(it.second);
				it.second = nullptr;
			}
		}
		shaders.clear();
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
		fullscreen = fs;
		if (fullscreen) {
			SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			glViewport(0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT);
		} else {
			SDL_SetWindowFullscreen(gWindow, SDL_FALSE);
			glViewport(0, 0, WIDTH, HEIGHT);
		}
	}

	void GLManager::ToggleFullscreen() {
		SetFullscreen(!fullscreen);
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
	FT_Library GLManager::lFreetype = nullptr;

	bool GLManager::fullscreen = false;
	bool GLManager::ready = false;
	map<string, Shader*> GLManager::shaders;

	unsigned int GLManager::DESKTOP_WIDTH;
	unsigned int GLManager::DESKTOP_HEIGHT;
	unsigned int GLManager::WIDTH;
	unsigned int GLManager::HEIGHT;
}



