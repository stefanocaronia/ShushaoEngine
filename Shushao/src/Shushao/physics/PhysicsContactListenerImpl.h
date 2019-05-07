#include <Box2D/Box2D.h>

#include "Collider2d.h"
#include "Collision2d.h"
#include "PhysicsContactListener.h"

#include "Shushao/Entity.h"

namespace se {

class PhysicsContactListener::Impl : public b2ContactListener {
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    /*void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse); */
    void BuildCollisions(b2Contact*, Collider2D*, Collider2D*, Collision2D&, Collision2D&);
};

PhysicsContactListener::PhysicsContactListener() : impl(new Impl()) {
}

void PhysicsContactListener::Impl::BeginContact(b2Contact* contact) {
    if (!contact->IsTouching()) return;

    Collider2D* colliderA = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureA()->GetUserData());
    Collider2D* colliderB = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureB()->GetUserData());

    Collision2D collisionA, collisionB;
    BuildCollisions(contact, colliderA, colliderB, collisionA, collisionB);

    if (colliderA != nullptr) {
        if (colliderA->isSensor) {
            colliderA->entity->InvokeMethod("OnTriggerEnter2D", *colliderB);
            colliderA->ColliderEnter(colliderB);
        } else {
            colliderA->entity->InvokeMethod("OnCollisionEnter2D", collisionA);
        }
    }

    if (colliderB != nullptr) {
        if (colliderB->isSensor) {
            colliderB->entity->InvokeMethod("OnTriggerEnter2D", *colliderA);
            colliderB->ColliderEnter(colliderA);
        } else {
            colliderB->entity->InvokeMethod("OnCollisionEnter2D", collisionB);
        }
    }
}

void PhysicsContactListener::Impl::EndContact(b2Contact* contact) {
    Collider2D* colliderA = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureA()->GetUserData());
    Collider2D* colliderB = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureB()->GetUserData());

    Collision2D collisionA, collisionB;
    BuildCollisions(contact, colliderA, colliderB, collisionA, collisionB);

    if (colliderA != nullptr) {
        if (colliderA->isSensor) {
            colliderA->entity->InvokeMethod("OnTriggerExit2D", *colliderB);
            colliderA->ColliderExit(colliderB);
        } else {
            colliderA->entity->InvokeMethod("OnCollisionExit2D", collisionA);
        }
    }

    if (colliderB != nullptr) {
        if (colliderB->isSensor) {
            colliderB->entity->InvokeMethod("OnTriggerExit2D", *colliderA);
            colliderB->ColliderExit(colliderA);
        } else {
            colliderB->entity->InvokeMethod("OnCollisionExit2D", collisionB);
        }
    }
}

void PhysicsContactListener::Impl::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    //std::cout << "PreSolve" << std::endl;

    Collider2D* colliderA = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureA()->GetUserData());
    Collider2D* colliderB = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureB()->GetUserData());

    Collision2D collisionA, collisionB;
    BuildCollisions(contact, colliderA, colliderB, collisionA, collisionB);

    if (colliderA != nullptr) colliderA->entity->InvokeMethod("OnCollisionStay2D", collisionA);
    if (colliderB != nullptr) colliderB->entity->InvokeMethod("OnCollisionStay2D", collisionB);
}

/*void PhysicsContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

		//std::cout << "PostSolve" << std::endl;

	}*/

void PhysicsContactListener::Impl::BuildCollisions(b2Contact* contact, Collider2D* colliderA, Collider2D* colliderB, Collision2D& collisionA, Collision2D& collisionB) {
    /*b2Manifold* manifold;
		contact->GetWorldManifold(&manifold);
		std::vector<glm::vec2> cpoints;
		for (int i = 0; i < manifold.pointCount; ++i)
			cpoints.push_back({manifold.points[i].localPoint.x, manifold.points[i].localPoint.y});
		glm::vec2 normal = {manifold.localNormal.x, manifold.localNormal.y};*/

    collisionA.collider = colliderA;
    collisionA.entity = colliderA->entity;
    collisionA.rigidbody = colliderA->rigidbody;
    collisionA.transform = colliderA->transform;
    //collisionA.contacts = cpoints;
    //collisionA.normal = normal;
    collisionA.enabled = contact->IsEnabled();
    collisionA.otherCollider = colliderB;
    collisionA.otherRigidbody = colliderB->rigidbody;

    collisionB.collider = colliderB;
    collisionB.entity = colliderB->entity;
    collisionB.rigidbody = colliderB->rigidbody;
    collisionB.transform = colliderB->transform;
    //collisionA.contacts = cpoints;
    //collisionA.normal = normal;
    collisionB.enabled = contact->IsEnabled();
    collisionB.otherCollider = colliderA;
    collisionB.otherRigidbody = colliderA->rigidbody;
}

}  // namespace se
