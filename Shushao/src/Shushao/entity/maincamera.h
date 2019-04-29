#pragma once

#include "../camera.h"
#include "../entity.h"

namespace se {

class SHUSHAO_API MainCamera : public Entity {
public:
    void Awake();

    Camera* camera;
};

}  // namespace se
