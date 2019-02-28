#pragma once

#include <map>
#include <string>
#include <SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.h"

namespace se {

	class GLManager {

		public:

			static SDL_GLContext gContext;
			static SDL_Window* gWindow;
			static SDL_Renderer* gRenderer;

			static FT_Library lFreetype;

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

			static Shader* AddShader(Shader* shader) {
				shaders[shader->name] = shader;
				return shader;
			}

			template <class T>
			static T* GetShader(std::string name) {
				auto it = shaders.find(name);
				if (it == shaders.end()) return nullptr;
				return (T*)shaders[name];
			}

			static Shader* GetShader(std::string name) {
				auto it = shaders.find(name);
				if (it == shaders.end()) return nullptr;
				return (Shader*)shaders[name];
			}

		private:

			static std::map<std::string, Shader*> shaders;

	};

}
