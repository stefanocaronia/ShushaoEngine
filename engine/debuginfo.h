#pragma once

#include "text.h"

namespace se {

class DebugInfo : public Component {
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
