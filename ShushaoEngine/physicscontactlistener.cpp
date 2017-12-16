#include "physicscontactlistener.h"

#include "collision2d.h"
#include "collider2d.h"
#include "entity.h"

namespace ShushaoEngine {

	void PhysicsContactListener::BeginContact(b2Contact* contact) {

		if (!contact->IsTouching()) return;

		Collider2D* colliderA = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureA()->GetUserData());
		Collider2D* colliderB = dynamic_cast<Collider2D*>((Collider2D*)contact->GetFixtureB()->GetUserData());

		/*b2Manifold* manifold;
		contact->GetWorldManifold(&manifold);
		std::vector<glm::vec2> cpoints;
		for (int i = 0; i < manifold.pointCount; ++i)
			cpoints.push_back({manifold.points[i].localPoint.x, manifold.points[i].localPoint.y});
		glm::vec2 normal = {manifold.localNormal.x, manifold.localNormal.y};*/

		Collision2D* collisionA = new Collision2D();
		collisionA->collider = colliderA;
		collisionA->entity = colliderA->entity;
		collisionA->rigidbody = colliderA->rigidbody;
		collisionA->transform = colliderA->transform;
		//collisionA.contacts = cpoints;
		//collisionA.normal = normal;
		collisionA->enabled = contact->IsEnabled();
		collisionA->otherCollider = colliderB;
		collisionA->otherRigidbody = colliderB->rigidbody;
		//collisionA.relativeVelocity = contact->GetTangentSpeed().;

		Collision2D* collisionB = new Collision2D();
		collisionA->collider = colliderB;
		collisionA->entity = colliderB->entity;
		collisionA->rigidbody = colliderB->rigidbody;
		collisionA->transform = colliderB->transform;
		//collisionA.contacts = cpoints;
		//collisionA.normal = normal;
		collisionA->enabled = contact->IsEnabled();
		collisionA->otherCollider = colliderA;
		collisionA->otherRigidbody = colliderA->rigidbody;
		//collisionA.relativeVelocity = contact->GetTangentSpeed();

		colliderA->entity->SendMessage("OnCollisionEnter2D", collisionA);
		colliderB->entity->SendMessage("OnCollisionEnter2D", collisionB);
	}

	void PhysicsContactListener::EndContact(b2Contact* contact) {

	}

	void PhysicsContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {

	}

}
