#pragma once

#include "Shushao/Core.h"

#include "PhysicsContactFilter.h"
#include "PhysicsContactListener.h"
#include "PhysicsDebugDraw.h"

namespace se {

class Physics {
public:
    static bool enabled;
    static bool debug;

    static bool doSleep;
    static float timeStep;
    static int velocityIterations;
    static int positionIterations;

    static PhysicsDebugDraw debugDraw;
    static PhysicsContactListener contactListener;
    static PhysicsContactFilter contactFilter;

    void setGravity(glm::vec3);

    static bool init();
    static void update();
    static void exit();

    class Impl;  // Pimpl!
    static std::shared_ptr<Impl> impl;
};

}  // namespace se
