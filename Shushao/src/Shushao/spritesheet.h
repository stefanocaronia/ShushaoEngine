#pragma once

#include "Core.h"
#include "sepch.h"
#include "object.h"
#include "sprite.h"
#include "textureatlas.h"

namespace se {

class SHUSHAO_API SpriteSheet : public Object, public std::vector<Sprite*> {
public:
    SpriteSheet();
    SpriteSheet(std::string);
    SpriteSheet(TextureAtlas*);
    SpriteSheet(std::string, TextureAtlas*);
    ~SpriteSheet();

    short cursor = 0;

    Sprite* next();
    Sprite* prev();

    void Add(Sprite*);

    void Load(TextureAtlas*);

protected:
private:
};

}  // namespace se
