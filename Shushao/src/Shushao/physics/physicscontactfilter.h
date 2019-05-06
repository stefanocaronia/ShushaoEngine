#pragma once

#include <Box2D/Box2D.h>

#include "Shushao/Core.h"

namespace se {

class PhysicsContactFilter : public b2ContactFilter {
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
};
}  // namespace se
