#pragma once

#include "Shushao/Core.h"

#include "physicscontactfilter.h"
#include "physicscontactlistener.h"
#include "physicsdebugdraw.h"

namespace se {

class Physics {
public:
    static bool enabled;
    static bool debug;

    static b2World* world;

    static b2Vec2 gravity;
    static bool doSleep;
    static float32 timeStep;
    static int32 velocityIterations;
    static int32 positionIterations;

    static PhysicsDebugDraw debugDraw;
    static PhysicsContactListener contactListener;
    static PhysicsContactFilter contactFilter;

    void setGravity(glm::vec3);

    static bool init();
    static void update();
    static void exit();

private:
};

}  // namespace se
