#pragma once

#include "../entity.h"

namespace se {

class SHUSHAO_API DebugGrid : public Entity {
public:
    void Awake();

    float gridSize = 1000.0f;
    float gizmoMagnitude = 2.0f;
};

}  // namespace se
