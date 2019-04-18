#pragma once

#include <physics_.h>

namespace se {

class PhysicsContactFilter : public b2ContactFilter {
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
};
}  // namespace se
