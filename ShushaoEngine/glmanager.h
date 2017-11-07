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

		private:

			GLManager() {}
			GLManager(const GLManager&);
			GLManager& operator=(const GLManager&);

		public:

			static GLManager& GetInstance() {
				static GLManager instance;
				return instance;
			}

			SDL_GLContext gContext;
			SDL_Window* gWindow;
			SDL_Renderer* gRenderer;
			SDL_Joystick* Joystick;

			glm::mat4 Projection;
			glm::mat4 View;

			unsigned int DESKTOP_WIDTH = 1920;
			unsigned int DESKTOP_HEIGHT = 1080;
			unsigned int WIDTH = 800;
			unsigned int HEIGHT = 600;

			bool Fullscreen = false;

			static GLuint vertexbuffer;

			bool Init(string, bool);
			void Quit();

			void Clear();
			void Clear(float, float, float, float, float);

			void SetFullscreen(bool);
			void ToggleFullscreen();
			void Swap();
			void Reset();

	};

}
