#pragma once

#include "Shushao/Core.h"
#include "Shushao/shaders/Shader.h"
#include "Shushao/Vao.h"

namespace se {

class PhysicsDebugDraw {
public:
    PhysicsDebugDraw();
    ~PhysicsDebugDraw() {
        if (impl) delete impl;
    }

    class Impl;  // Pimpl!
    Impl* impl;
};

}  // namespace se
