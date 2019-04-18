#pragma once

#include <core_.h>
#include <math_.h>
#include <opengl_.h>
#include <sdl_.h>
#include <std_.h>

#include "resource.h"

namespace se {

class Texture : public Object, public Resource {
public:
    Texture(std::string filename = "", std::string n = "");

    ~Texture();

    int height;
    int width;
    glm::vec2 size;

    bool Load(std::string);
    bool LoadEmbedded(int IDRES, std::string library = "");
    bool LoadBytes(std::vector<char> data);
    bool Bind(SDL_Surface* surface);

    GLuint GetTextureID();
    SDL_Surface* GetSurface();

    GLuint TextureID = 0;

    SDL_Surface* Surface;
    //SDL_Texture* SDLTexture;
};

}  // namespace se
