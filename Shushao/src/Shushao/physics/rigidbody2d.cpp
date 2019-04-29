#include "rigidbody2d.h"
#include "physics.h"
#include "../transform.h"
#include "../entity.h"

namespace se {

	void Rigidbody2D::Copy(Rigidbody2D* other) {
		if (other == nullptr) return;
		Component::Copy(other);

		position = other->position;
		velocity = other->velocity;
		angle = other->angle;
		angularVelocity = other->angularVelocity;
		fixedRotation = other->fixedRotation;
		type = other->type; // TODO: controllare che sia copy
	}

	void Rigidbody2D::OnDestroy() {
		if (body == nullptr) return;
		Physics::world->DestroyBody(body);
	}

	void Rigidbody2D::Awake() {

		position = transform->position;
		angle = transform->GetEulerAngles().z;

		/// DA CAPIRE, se devo lasciare dynamic (fa le collisioni con gli static) o no
		/*if (!transform->isAtRoot() && type == RigidbodyType::DYNAMIC) {
			type = RigidbodyType::KINEMATIC;
		}*/

		bodyDef.type = (b2BodyType)type;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.angle = angle * DEGTORAD; // RADIANS
		bodyDef.fixedRotation = fixedRotation;
		bodyDef.userData = this;
		bodyDef.active = enabled && entity->active;

		body = Physics::world->CreateBody(&bodyDef);
	}

	void Rigidbody2D::OnEnable() {
		body->SetActive(transform->isAtRoot() && entity->active);
	}

	void Rigidbody2D::OnDisable() {
		body->SetActive(false);
	}

	void Rigidbody2D::Update() {
		if (transform->isAtRoot()) {
			body->SetActive(entity->active);
		}
	}

	void Rigidbody2D::FixedUpdate() {

		if (type == RigidbodyType::STATIC) {
			position = transform->position;
			angle = transform->GetEulerAngles().z; // DEGREES
			body->SetTransform(b2Vec2(position.x, position.y), angle * DEGTORAD);
			return;
		}

		b2Vec2 p = body->GetPosition();
		b2Vec2 v = body->GetLinearVelocity();
		position = {p.x, p.y};
		velocity = {v.x, v.y};
		angle = body->GetAngle() * RADTODEG; // DEGREES
		angularVelocity = body->GetAngularVelocity();

		transform->SetPosition({position.x, position.y, transform->position.z});
		transform->SetRotation({0.0f, 0.0f, angle});
	}
}
