#pragma once

#include <GL/glew.h>
#include <SDL.h>

#include "object.h"

namespace se {

	class Texture : public Object {

		public:

			Texture(std::string filename = "", std::string n = "");

			~Texture();

			int height;
			int width;

			bool Load(std::string);

			GLuint GetTextureID();
			SDL_Surface* GetSurface();

			GLuint TextureID = 0;

			SDL_Surface* Surface;
			//SDL_Texture* SDLTexture;

	};

}
