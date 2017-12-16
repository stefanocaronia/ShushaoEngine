#include "physics.h"
#include "scenemanager.h"

#include "config.h"
#include "physicscontactlistener.h"
#include "physicsdebugdraw.h"

namespace ShushaoEngine {

	//{ #region Physics

	void Physics::init() {

		world = new b2World(gravity);

		world->SetAllowSleeping(doSleep);
		world->SetDebugDraw(&debugDraw);
		world->SetContactListener(&contactListener);

        debugDraw.init();
		debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);

		/*	e_shapeBit ( draw shapes )
		 *	e_jointBit ( draw joint connections
		 *	e_aabbBit ( draw axis aligned bounding boxes )
		 *	e_pairBit ( draw broad-phase pairs )
		 *	e_centerOfMassBit ( draw a marker at body CoM )
		 */
	}

	void Physics::setGravity(glm::vec3 gravity_) {
		if (!enabled) return;
		if (world == nullptr) return;
        gravity = b2Vec2(gravity_.x, gravity_.y);
        world->SetGravity(gravity);
	}

	void Physics::update() {
		if (!enabled) return;
		if (world == nullptr) return;
		world->Step(timeStep, velocityIterations, positionIterations);
	}

	void Physics::exit() {
		if (world == nullptr) return;
		delete world;
	}

	// initialization
	b2World* Physics::world = nullptr;
	bool Physics::enabled = Config::Physics::enabled;
	bool Physics::debug = Config::Physics::debug;
	b2Vec2 Physics::gravity = {Config::Physics::gravity.x, Config::Physics::gravity.y};
	float32 Physics::timeStep = 1.0f / Config::Time::fixedRateLimit;
	bool Physics::doSleep = Config::Physics::doSleep;
	int32 Physics::velocityIterations = Config::Physics::velocityIterations;
	int32 Physics::positionIterations = Config::Physics::positionIterations;
	PhysicsDebugDraw Physics::debugDraw;
	PhysicsContactListener Physics::contactListener;

	//}

}
