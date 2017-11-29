#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

#include "debug.h"
#include "utility.h"
#include "texture.h"

using namespace std;

namespace ShushaoEngine {

	Texture::Texture() {
		name = "Texture";
	}

	Texture::Texture(string filename, string n) {
		Load(filename);
		name = n;
	}

	Texture::Texture(string filename) {
		Load(filename);
		name = util::basename(filename);
	}

	Texture::~Texture()	{
		//SDL_FreeSurface(Surface);
		//SDL_DestroyTexture(SDLTexture);
		//SDLTexture = NULL;

		// TODO: liberare memoria
	}

	bool Texture::Load(string filename) {

		Surface = IMG_Load(filename.c_str());

		if (!Surface) {
			Debug::Log(ERROR) << "IMG_Load " << IMG_GetError() << endl;
			return false;
		}

		width = Surface->w;
		height = Surface->h;

		int Mode = Surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, Mode, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);

		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//SDLTexture = SDL_CreateTextureFromSurface(GLManager::gRenderer, Surface);

		SDL_FreeSurface(Surface);

		glBindTexture(GL_TEXTURE_2D, 0);

		if (TextureID)
			return true;
		else
			return false;
	}

	GLuint Texture::GetTextureID() {
		return TextureID;
	}

}
