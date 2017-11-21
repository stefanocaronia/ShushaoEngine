#pragma once

#include "object.h"
#include "glmanager.h"

namespace ShushaoEngine {

	class Texture : public Object {

		public:

			Texture();
			Texture(string);
			Texture(string, string);

			~Texture();

			int height;
			int width;

			bool Load(string);

			GLuint GetTextureID();
			SDL_Surface* GetSurface();

			GLuint TextureID = 0;

			SDL_Surface* Surface;
			//SDL_Texture* SDLTexture;

	};

}
