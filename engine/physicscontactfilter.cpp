#include "physicscontactfilter.h"

#include "collider2d.h"
#include "entity.h"
#include "transform.h"

namespace se {

	bool PhysicsContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) {

		Entity* A = ((Collider2D*)fixtureA->GetUserData())->entity;
		Entity* B = ((Collider2D*)fixtureB->GetUserData())->entity;

		if (A == B) return false;
		if (A->transform->GetParent() == B->transform) return false;
		if (B->transform->GetParent() == A->transform) return false;

		return true;
	}

}
