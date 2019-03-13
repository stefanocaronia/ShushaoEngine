#include <algorithm>

#include "collider2d.h"
#include "rigidbody2d.h"
#include "transform.h"
#include "entity.h"
#include "sprite.h"
#include "spriterenderer.h"

namespace se {

	//{ #region Collider2D (base virtual class)

	void Collider2D::setup() {
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		fixtureDef.isSensor = isSensor;
		fixtureDef.userData = this;
	}

	void Collider2D::OnDestroy() {
		/*if (fixture != nullptr && rigidbody != nullptr) {
			rigidbody->body->DestroyFixture(fixture);
		}*/
	}

	void Collider2D::ColliderEnter(Collider2D* other) {
		auto position = std::find(colliders.begin(), colliders.end(), other);
		if (position == colliders.end())
			colliders.push_back(other);
	}

	void Collider2D::ColliderExit(Collider2D* other) {
		auto position = std::find(colliders.begin(), colliders.end(), other);
		if (position != colliders.end())
			colliders.erase(position);
	}

	void Collider2D::SetDensity(float density_) {
		density = density_;
		fixtureDef.density = density;
		if (fixture != nullptr) fixture->SetDensity(density);
	}

	void Collider2D::SetRestitution(float restitution_) {
		restitution = restitution_;
		fixtureDef.restitution = restitution;
		if (fixture != nullptr) fixture->SetRestitution(restitution);
	}

	void Collider2D::SetFriction(float friction_) {
		friction = friction_;
		fixtureDef.friction = friction;
		if (fixture != nullptr) fixture->SetFriction(friction);
	}

	void Collider2D::SetSensor(bool sensor_) {
		isSensor = sensor_;
		fixtureDef.isSensor = isSensor;
		if (fixture != nullptr) fixture->SetSensor(sensor_);
	}

	void Collider2D::Awake() {
		scale = {transform->scale.x, transform->scale.y};
	}

	void Collider2D::Start() {
		Attach();
	}

	void Collider2D::FixedUpdate() {
        if (!colliders.empty()) {
			for (Collider2D* c : colliders) {
                entity->SendMessage("OnTriggerStay2D", *c);
			}
        }
	}

	void Collider2D::Attach() {
		rigidbody = entity->GetComponent<Rigidbody2D>();
		if (rigidbody == nullptr || rigidbody->body == nullptr)
			return;
		fixture = rigidbody->body->CreateFixture(&fixtureDef);
	}

	void Collider2D::Reset() {
        rigidbody->body->DestroyFixture(fixture);
        fixture = rigidbody->body->CreateFixture(&fixtureDef);
	}

	//}

	//{ #region CircleCollider2D

	void CircleCollider2D::SetShape(glm::vec2 position_, float radius_) {

		position = position_;
		radius = radius_;

		SpriteRenderer* sr = entity->GetComponent<SpriteRenderer>();
		if (sr != nullptr) {
			shape.m_p.Set(position_.x - sr->sprite->pivot.x * scale.x, position_.y - sr->sprite->pivot.y * scale.y);
		} else {
			shape.m_p.Set(position_.x, position_.y);
		}
		shape.m_radius = radius_ * scale.x;
		fixtureDef.shape = &shape;
	}

	void CircleCollider2D::ResetShape() {
		scale = {transform->scale.x, transform->scale.y};
		SetShape(position, radius);
	}

	//}

	//{ #region BoxCollider2D

	void BoxCollider2D::SetShape(glm::vec2 hsize) {

		SpriteRenderer* sr = entity->GetComponent<SpriteRenderer>();

		boxHalfSize = hsize;
		if (sr != nullptr) {
			b2Vec2 pivot(sr->sprite->pivot.x * scale.x, sr->sprite->pivot.y * scale.y);
			shape.SetAsBox(boxHalfSize.x * scale.x, boxHalfSize.y * scale.y, -pivot, 0.0f);
		} else {
			 shape.SetAsBox(boxHalfSize.x * scale.x, boxHalfSize.y * scale.y);
		}
        fixtureDef.shape = &shape;
	}

	void BoxCollider2D::ResetShape() {
		scale = {transform->scale.x, transform->scale.y};
		SetShape(boxHalfSize);
	}

	//}

	//{ #region EdgeCollider2D

	void EdgeCollider2D::SetShape(glm::vec2 start, glm::vec2 end) {
		shape.Set(b2Vec2(start.x, start.y), b2Vec2(end.x, end.y));
		fixtureDef.shape = &shape;
	}

	//}

	//{ #region PolygonCollider2D

	void PolygonCollider2D::SetShape(std::vector<glm::vec2>) {}

	//}
}
