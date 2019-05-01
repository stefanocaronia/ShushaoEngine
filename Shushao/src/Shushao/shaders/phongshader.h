#pragma once

#include "../Core.h"
#include "shader.h"

namespace se {

class SHUSHAO_API PhongShader : public Shader {
public:
    PhongShader();

protected:
    void Awake();
    void Update();
};

}  // namespace se
