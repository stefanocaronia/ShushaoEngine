#pragma once

#include "../camera.h"
#include "../entity.h"

namespace se {

class MainCamera : public Entity {
public:
    void Awake();

    Camera* camera;
};

}  // namespace se
