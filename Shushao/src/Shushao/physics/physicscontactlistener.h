#pragma once

#include "Collider2d.h"

namespace se {

class PhysicsContactListener {
public:
    PhysicsContactListener();
    ~PhysicsContactListener() {
        if (impl) delete impl;
    }

    class Impl;  // Pimpl!
    Impl* impl;
};

}  // namespace se
