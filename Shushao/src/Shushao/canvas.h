#pragma once

#include "Shushao/Core.h"
#include "sepch.h"

#include "camera.h"
#include "config.h"
#include "rect.h"
#include "renderer.h"

namespace se {

class SHUSHAO_API Canvas : public Component {
public:
    virtual void setup();
    ~Canvas();

    const RenderMode& renderMode = _renderMode;
    Camera* camera = nullptr;

    std::vector<Component*> ChildRenderers;

    Canvas* SetRenderMode(RenderMode value);
    Canvas* SetCamera(Camera* camera_);

    void Awake();
    void Update();
    void Render();
    void OnDestroy();

    void Copy(Canvas* other);

private:
    RenderMode _renderMode = RenderMode::WORLD;
    RenderMode _lastRenderMode;
    void processRenderMode();
};

}  // namespace se
