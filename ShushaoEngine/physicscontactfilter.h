#pragma once

#include <Box2D/Box2D.h>


namespace ShushaoEngine {

	class PhysicsContactFilter : public b2ContactFilter {

		bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);

	};
}
