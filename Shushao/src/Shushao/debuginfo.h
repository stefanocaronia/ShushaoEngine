#pragma once

#include "core.h"

#include "text.h"

namespace se {

class SHUSHAO_API DebugInfo : public Component {
public:
    Text* times = nullptr;

    double updateTime;
    double renderTime;
    double frameRate;
    double fixedTime;

protected:
    void Awake();
    void Update();
};

}  // namespace se
