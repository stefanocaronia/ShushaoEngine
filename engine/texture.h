#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <vector>
#include <string>

#include "object.h"
#include "resource.h"

namespace se {

	class Texture : public Object, public Resource {

		public:

			Texture(std::string filename = "", std::string n = "");

			~Texture();

			int height;
			int width;

			bool Load(std::string);
			bool LoadEmbedded(int IDRES);
			bool LoadBytes(std::vector<char> data);
			bool Bind(SDL_Surface* surface);

			GLuint GetTextureID();
			SDL_Surface* GetSurface();

			GLuint TextureID = 0;

			SDL_Surface* Surface;
			//SDL_Texture* SDLTexture;

	};

}
