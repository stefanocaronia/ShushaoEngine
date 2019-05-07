#include <Box2D/Box2D.h>

#include "Physics.h"
#include "PhysicsContactFilter.h"
#include "PhysicsContactFilterImpl.h"
#include "PhysicsContactListener.h"
#include "PhysicsContactListenerImpl.h"
#include "PhysicsDebugDraw.h"
#include "PhysicsDebugDrawImpl.h"

#include "Shushao/Config.h"
#include "Shushao/SceneManager.h"

namespace se {

// initializations
std::shared_ptr<Physics::Impl> Physics::impl = std::make_shared<Physics::Impl>();
bool Physics::enabled;
bool Physics::debug;
float32 Physics::timeStep;
bool Physics::doSleep;
int32 Physics::velocityIterations;
int32 Physics::positionIterations;
PhysicsDebugDraw Physics::debugDraw;
PhysicsContactListener Physics::contactListener;
PhysicsContactFilter Physics::contactFilter;

class Physics::Impl {
public:
    static b2World* world;
    static b2Vec2 gravity;
};

bool Physics::init() {
    enabled = Config::Physics::enabled;
    debug = Config::Physics::debug;
    impl->gravity = {Config::Physics::gravity.x, Config::Physics::gravity.y};
    timeStep = 1.0f / Config::Time::fixedRateLimit;
    doSleep = Config::Physics::doSleep;
    velocityIterations = Config::Physics::velocityIterations;
    positionIterations = Config::Physics::positionIterations;

    impl->world = new b2World(impl->gravity);
    impl->world->SetAllowSleeping(doSleep);
    impl->world->SetContactListener(contactListener.impl);
    impl->world->SetContactFilter(contactFilter.impl);

    if (debug) {
        impl->world->SetDebugDraw(debugDraw.impl);
        debugDraw.impl->SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
        /*	e_shapeBit ( draw shapes )
			 *	e_jointBit ( draw joint connections
			 *	e_aabbBit ( draw axis aligned bounding boxes )
			 *	e_pairBit ( draw broad-phase pairs )
			 *	e_centerOfMassBit ( draw a marker at body CoM )
			 */
        debugDraw.impl->Init();
    }

    return true;
}

void Physics::setGravity(glm::vec3 gravity_) {
    if (!enabled) return;
    if (impl->world == nullptr) return;
    impl->gravity = b2Vec2(gravity_.x, gravity_.y);
    impl->world->SetGravity(impl->gravity);
}

void Physics::update() {
    if (!enabled) return;
    if (impl->world == nullptr) return;
    impl->world->Step(timeStep, velocityIterations, positionIterations);
}

void Physics::exit() {
    if (impl->world == nullptr) return;
    delete impl->world;
}

}  // namespace se
