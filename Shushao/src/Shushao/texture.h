#pragma once

#include <glad/glad.h>

#include "Shushao/Core.h"
#include "sepch.h"

#include "object.h"
#include "resource.h"

namespace se {

class SHUSHAO_API Texture : public Object, public Resource {
public:
    Texture(std::string filename = "", std::string n = "");

    ~Texture();

    int height;
    int width;
    glm::vec2 size;

    bool Load(std::string);
    bool LoadEmbedded(int IDRES, std::string library = "");
    bool LoadBytes(std::vector<char> data);

    GLuint GetTextureID();
    GLuint TextureID = 0;

private:
    void Bind(unsigned char* image_);
};

}  // namespace se
