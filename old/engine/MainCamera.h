#pragma once

#include "Camera.h"
#include "Entity.h"

namespace se {

class SHUSHAO_API MainCamera : public Entity {
public:
    void Awake();

    Camera* camera;
};

}  // namespace se
