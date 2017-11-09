#pragma once

#include <glm.hpp>
#include <vector>

#include "libs.h"
#include "camera.h"

using namespace std;
using namespace glm;

namespace ShushaoEngine {

	class Sprite;
	class Texture;
	class SpriteRenderer;
	class Transform;

	class GLManager {

		public:

			static SDL_GLContext gContext;
			static SDL_Window* gWindow;
			static SDL_Renderer* gRenderer;
			static SDL_Joystick* Joystick;

			static mat4 Projection;
			static mat4 View;

			static bool Fullscreen;

			static unsigned int DESKTOP_WIDTH;
			static unsigned int DESKTOP_HEIGHT;
			static unsigned int WIDTH;
			static unsigned int HEIGHT;

			static bool Init(string, bool);
			static void Quit();

			static void Clear();
			static void Clear(float, float, float, float, float);

			static void SetFullscreen(bool);
			static void ToggleFullscreen();
			static void Swap();
			static void Reset();
	};

}
