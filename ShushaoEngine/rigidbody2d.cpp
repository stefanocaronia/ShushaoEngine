#include "rigidbody2d.h"
#include "physics.h"
#include "transform.h"
#include "entity.h"

namespace ShushaoEngine {

	void Rigidbody2D::OnDestroy() {
		if (body == nullptr) return;
		Physics::world->DestroyBody(body);
	}

	void Rigidbody2D::Awake() {

		position = transform->position;
		angle = transform->getEulerAngles().z * DEGTORAD;

		bodyDef.type = (b2BodyType)type;
		bodyDef.position.Set(position.x, position.y);
		bodyDef.angle = angle;
		bodyDef.fixedRotation = fixedRotation;
		bodyDef.userData = entity;
		bodyDef.active = enabled && transform->isAtRoot() && entity->activeSelf;

		body = Physics::world->CreateBody(&bodyDef);
	}

	void Rigidbody2D::OnEnable() {
		body->SetActive(transform->isAtRoot() && entity->activeSelf);
	}

	void Rigidbody2D::OnDisable() {
		body->SetActive(false);
	}

	void Rigidbody2D::Update() {
		if (transform->isAtRoot()) {
			body->SetActive(entity->activeSelf);
		}
	}

	void Rigidbody2D::FixedUpdate() {

		if (!transform->isAtRoot() || type == RigidbodyType::STATIC) {
			position = transform->position;
			angle = transform->getEulerAngles().z * DEGTORAD;
			body->SetTransform(b2Vec2(position.x, position.y), angle);
			return;
		}

		b2Vec2 p = body->GetPosition();
		b2Vec2 v = body->GetLinearVelocity();
		position = {p.x, p.y};
		velocity = {v.x, v.y};
		angle = body->GetAngle();
		angularVelocity = body->GetAngularVelocity();

		transform->setPosition({position.x, position.y, transform->position.z});
		transform->setLocalRotation({0.0f,0.0f, angle});
	}
}
