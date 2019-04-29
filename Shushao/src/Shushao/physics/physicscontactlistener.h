#pragma once

#include "../core.h"

#include "collider2d.h"

namespace se {

class SHUSHAO_API PhysicsContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    /*void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
*/
    void BuildCollisions(b2Contact*, Collider2D*, Collider2D*, Collision2D&, Collision2D&);
};
}  // namespace se