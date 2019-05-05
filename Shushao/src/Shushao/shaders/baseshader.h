#pragma once

#include "Shushao/Core.h"
#include "shader.h"

namespace se {

class SHUSHAO_API BaseShader : public Shader {
public:
    BaseShader();

    void Awake();
};

}  // namespace se
