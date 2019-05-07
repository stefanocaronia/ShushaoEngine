#pragma once

namespace se {

class b2ContactFilter;
class b2Fixture;

class PhysicsContactFilter : public b2ContactFilter {
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
};

}  // namespace se
