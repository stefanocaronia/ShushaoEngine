#pragma once

#include "collider2d.h"

namespace se {

class b2Contact;
class b2Manifold;

class PhysicsContactListener : public b2ContactListener {
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    /*void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
*/
    void BuildCollisions(b2Contact*, Collider2D*, Collider2D*, Collision2D&, Collision2D&);
};

}  // namespace se
