#pragma once

#include <vector>
#include <string>
#include <SDL.h>

namespace ShushaoEngine {

	class GLManager {

		public:

			static SDL_GLContext gContext;
			static SDL_Window* gWindow;
			static SDL_Renderer* gRenderer;

			static bool fullscreen;
			static bool ready;

			static unsigned int DESKTOP_WIDTH;
			static unsigned int DESKTOP_HEIGHT;
			static unsigned int WIDTH;
			static unsigned int HEIGHT;

			static bool Init(std::string, bool);
			static void Quit();

			static void Clear();
			static void Clear(float, float, float, float, float);

			static void SetFullscreen(bool);
			static void ToggleFullscreen();
			static void Swap();
			static void Reset();
	};

}
