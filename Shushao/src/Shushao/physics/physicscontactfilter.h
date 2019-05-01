#pragma once

#include "../Core.h"

namespace se {

class SHUSHAO_API PhysicsContactFilter : public b2ContactFilter {
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
};
}  // namespace se
