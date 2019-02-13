#include <string>
#include <SDL_image.h>

#include "texture.h"
#include "debug.h"
#include "utility.h"

namespace se {

	Texture::Texture(std::string filename, std::string n) {
		if (filename != "") Load(filename);
		name = (n == "" ? util::basename(filename) : n);
	}

	Texture::~Texture()	{
		const GLuint textures[] = {TextureID};
		glDeleteTextures(1, textures);
	}

	bool Texture::Load(std::string filename) {

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

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(GL_TEXTURE_2D);

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
