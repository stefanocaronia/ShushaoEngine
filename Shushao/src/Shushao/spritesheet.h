#pragma once

#include "Core.h"
#include "Object.h"
#include "sepch.h"
#include "Sprite.h"
#include "TextureAtlas.h"

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
