#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <vector>

#include "physics/physicscontactlistener.h"
#include "physics/physicscontactfilter.h"
#include "physics/physicsdebugdraw.h"

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

			static void init();
			static void update();
			static void exit();

		private:

	};


}
