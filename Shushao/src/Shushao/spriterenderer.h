#pragma once

#include "core.h"

#include "color.h"
#include "material.h"
#include "renderer.h"
#include "shaders/shader.h"
#include "sprite.h"

namespace se {

class SHUSHAO_API SpriteRenderer : public Renderer {
public:
    virtual void setup();
    ~SpriteRenderer();

    bool isReady();

    Sprite* sprite = nullptr;
    Material* material = nullptr;

    SpriteRenderer* SetSprite(Sprite* sprite_) {
        sprite = sprite_;
        return this;
    }

    SpriteRenderer* SetMaterial(Material* material_) {
        material = material_;
        return this;
    }

    Color color = {1.0f, 1.0f, 1.0f, 1.0f};  //	Rendering color for the Sprite graphic.
    bool flipX;  //	Flips the sprite on the X axis.
    bool flipY;  //	Flips the sprite on the Y axis.
    glm::vec2 size;  //	Property to set/get the size to render when the SpriteRenderer.drawMode is set to SpriteDrawMode.NineSlice.

protected:
    void Awake();
    void Update();
    void Render();
    void OnDestroy();
};

}  // namespace se