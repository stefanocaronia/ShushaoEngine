#include "physicscontactlistener.h"

#include "collision2d.h"
#include "collider2d.h"
#include "entity.h"

namespace se {

	void PhysicsContactListener::BeginContact(b2Contact* contact) {

		if (!contact->IsTouching()) return;

		Collider2D* colliderA = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureA()->GetUserData());
		Collider2D* colliderB = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureB()->GetUserData());

		Collision2D collisionA, collisionB;
		BuildCollisions(contact, colliderA, colliderB, collisionA, collisionB);

		if (colliderA != nullptr) {
			if (colliderA->isSensor) {
				colliderA->entity->SendMessage("OnTriggerEnter2D", *colliderB);
				colliderA->ColliderEnter(colliderB);
			} else {
				colliderA->entity->SendMessage("OnCollisionEnter2D", collisionA);
			}
		}

		if (colliderB != nullptr) {
			if (colliderB->isSensor) {
				colliderB->entity->SendMessage("OnTriggerEnter2D", *colliderA);
				colliderB->ColliderEnter(colliderA);
			} else {
				colliderB->entity->SendMessage("OnCollisionEnter2D", collisionB);
			}
		}
	}

	void PhysicsContactListener::EndContact(b2Contact* contact) {

		Collider2D* colliderA = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureA()->GetUserData());
		Collider2D* colliderB = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureB()->GetUserData());

		Collision2D collisionA, collisionB;
		BuildCollisions(contact, colliderA, colliderB, collisionA, collisionB);

		if (colliderA != nullptr) {
			if (colliderA->isSensor) {
				colliderA->entity->SendMessage("OnTriggerExit2D", *colliderB);
				colliderA->ColliderExit(colliderB);
			} else {
				colliderA->entity->SendMessage("OnCollisionExit2D", collisionA);
			}
		}

		if (colliderB != nullptr) {
			if (colliderB->isSensor) {
				colliderB->entity->SendMessage("OnTriggerExit2D", *colliderA);
				colliderB->ColliderExit(colliderA);
			} else {
				colliderB->entity->SendMessage("OnCollisionExit2D", collisionB);
			}
		}
	}

	void PhysicsContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

		//std::cout << "PreSolve" << endl;

		Collider2D* colliderA = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureA()->GetUserData());
		Collider2D* colliderB = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureB()->GetUserData());

		Collision2D collisionA, collisionB;
		BuildCollisions(contact, colliderA, colliderB, collisionA, collisionB);

		if (colliderA != nullptr) colliderA->entity->SendMessage("OnCollisionStay2D", collisionA);
		if (colliderB != nullptr) colliderB->entity->SendMessage("OnCollisionStay2D", collisionB);
	}

	/*void PhysicsContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

		//std::cout << "PostSolve" << endl;

	}*/

	void PhysicsContactListener::BuildCollisions(b2Contact* contact, Collider2D* colliderA, Collider2D* colliderB, Collision2D& collisionA, Collision2D& collisionB) {

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

}
