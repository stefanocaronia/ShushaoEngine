#pragma once

#include "../shaders/shader.h"
#include "../vao.h"
#include "Shushao/Core.h"

namespace se {

class PhysicsDebugDraw {
public:
    class Impl;
    std::unique_ptr<Impl> impl;
};

}  // namespace se
