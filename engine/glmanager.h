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
				shaders.push_back(shader);
				return shader;
			}

			template<class T>
			static T* GetShader(std::string _name = "") {	// Returns the component of Type type if the game object has one attached, null if it doesn't.
				for(auto& shader: shaders) {
					if (dynamic_cast<T*>(shader)) {
						if (_name == "" || shader->name == _name) return dynamic_cast<T*>(shader);
					}
				}
				return nullptr;
			}

		private:

			static std::vector<Shader*> shaders;

	};

}
