#include "physics/physics.h"
#include "scenemanager.h"

#include "config.h"
#include "physics/physicscontactlistener.h"
#include "physics/physicsdebugdraw.h"

namespace se {

	void Physics::init() {

		enabled = Config::Physics::enabled;
		debug = Config::Physics::debug;
		gravity = {Config::Physics::gravity.x, Config::Physics::gravity.y};
		timeStep = 1.0f / Config::Time::fixedRateLimit;
		doSleep = Config::Physics::doSleep;
		velocityIterations = Config::Physics::velocityIterations;
		positionIterations = Config::Physics::positionIterations;

		world = new b2World(gravity);
		world->SetAllowSleeping(doSleep);
		world->SetContactListener(&contactListener);
		world->SetContactFilter(&contactFilter);

		if (debug) {
			world->SetDebugDraw(&debugDraw);
			debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
			/*	e_shapeBit ( draw shapes )
			 *	e_jointBit ( draw joint connections
			 *	e_aabbBit ( draw axis aligned bounding boxes )
			 *	e_pairBit ( draw broad-phase pairs )
			 *	e_centerOfMassBit ( draw a marker at body CoM )
			 */
			debugDraw.Init();
		}
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
	bool Physics::enabled;
	bool Physics::debug;
	b2Vec2 Physics::gravity;
	float32 Physics::timeStep;
	bool Physics::doSleep;
	int32 Physics::velocityIterations;
	int32 Physics::positionIterations;
	PhysicsDebugDraw Physics::debugDraw;
	PhysicsContactListener Physics::contactListener;
	PhysicsContactFilter Physics::contactFilter;
}
