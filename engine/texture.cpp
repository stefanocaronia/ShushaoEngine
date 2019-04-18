#include <core_.h>
#include <opengl_.h>
#include <sdl_.h>
#include <std_.h>

#include "resources.h"
#include "texture.h"
#include "utility.h"

namespace se {

using namespace std;

Texture::Texture(std::string filename, std::string n) {
    if (filename != "") Load(filename);
    name = (n == "" ? util::basename(filename) : n);
}

Texture::~Texture() {
    const GLuint textures[] = {TextureID};
    glDeleteTextures(1, textures);
}

bool Texture::LoadEmbedded(int IDRES, std::string library) {
    vector<char> data = Resources::GetEmbeddedData(IDRES, library);
    return LoadBytes(data);
}

bool Texture::LoadBytes(std::vector<char> data) {
    SDL_RWops* rw = SDL_RWFromMem(&data[0], data.size());
    Surface = IMG_LoadPNG_RW(rw);

    if (Surface == nullptr) {
        Debug::Log(WARNING) << "Can't load embedded image '" << name << "': " << IMG_GetError() << endl;
        return false;
    }
    return Bind(Surface);
}

bool Texture::Load(std::string filename) {
    Surface = IMG_Load(filename.c_str());
    name = util::basename(filename);

    if (!Surface) {
        Debug::Log(ERROR) << "IMG_Load " << IMG_GetError() << endl;
        return false;
    }

    return Bind(Surface);
}

bool Texture::Bind(SDL_Surface* surface) {
    if (Surface == nullptr) return false;
    width = surface->w;
    height = surface->h;
    size = {width, height};

    int Mode = (surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB);

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, Surface->pixels);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(surface);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (TextureID)
        return true;
    else
        return false;
}

GLuint Texture::GetTextureID() {
    return TextureID;
}

}  // namespace se
