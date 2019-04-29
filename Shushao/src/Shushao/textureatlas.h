#pragma once

#include "core.h"
#include "rect.h"
#include "sprite.h"
#include "texture.h"

namespace se {

class SHUSHAO_API TextureAtlas : public Texture {
public:
    TextureAtlas(){};
    TextureAtlas(std::string filename) : Texture(filename){};
    TextureAtlas(std::string filename, std::string n) : Texture(filename, n){};

    std::vector<std::pair<Rect, Align>> slices;

    void AddSlice(Rect, Align pp = Align::CENTER);

    void AddGrid(
        glm::vec2,
        Align pp = Align::CENTER,
        glm::vec2 = glm::vec2(0, 0),
        glm::vec2 = glm::vec2(0, 0));
};

}  // namespace se
