#include <Box2D/Box2D.h>

#include "Shushao/Entity.h"
#include "Shushao/Sprite.h"
#include "Shushao/spriteRenderer.h"
#include "Shushao/transform.h"

#include "Collider2d.h"
#include "Rigidbody2d.h"
#include "Rigidbody2dImpl.h"

namespace se {

//{ #region Collider2D (base virtual class)

struct Collider2D::Impl {
    b2FixtureDef fixtureDef;
    b2Fixture* fixture = nullptr;
};

Collider2D::Collider2D() : collider(new Impl()) {}

void Collider2D::setup() {
    collider->fixtureDef.density = density;
    collider->fixtureDef.friction = friction;
    collider->fixtureDef.restitution = restitution;
    collider->fixtureDef.isSensor = isSensor;
    collider->fixtureDef.userData = this;
}

void Collider2D::OnDestroy() {
    /*if (fixture != nullptr && rigidbody != nullptr) {
		rigidbody->body->DestroyFixture(fixture);
	}*/
}

void Collider2D::ColliderEnter(Collider2D* other) {
    auto position = std::find(colliders.begin(), colliders.end(), other);
    if (position == colliders.end()) {
        colliders.push_back(other);
    }
}

void Collider2D::ColliderExit(Collider2D* other) {
    auto position = std::find(colliders.begin(), colliders.end(), other);
    if (position != colliders.end()) {
        colliders.erase(position);
    }
}

void Collider2D::SetDensity(float density_) {
    density = density_;
    collider->fixtureDef.density = density;
    if (collider->fixture != nullptr) {
        collider->fixture->SetDensity(density);
    }
}

void Collider2D::SetRestitution(float restitution_) {
    restitution = restitution_;
    collider->fixtureDef.restitution = restitution;
    if (collider->fixture != nullptr) {
        collider->fixture->SetRestitution(restitution);
    }
}

void Collider2D::SetFriction(float friction_) {
    friction = friction_;
    collider->fixtureDef.friction = friction;
    if (collider->fixture != nullptr) {
        collider->fixture->SetFriction(friction);
    }
}

void Collider2D::SetSensor(bool sensor_) {
    isSensor = sensor_;
    collider->fixtureDef.isSensor = isSensor;
    if (collider->fixture != nullptr) {
        collider->fixture->SetSensor(sensor_);
    }
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
            entity->InvokeMethod("OnTriggerStay2D", *c);
        }
    }
}

void Collider2D::Attach() {
    rigidbody = entity->GetComponent<Rigidbody2D>();
    if (rigidbody == nullptr || rigidbody->info->body == nullptr) {
        return;
    }
    collider->fixture = rigidbody->info->body->CreateFixture(&(collider->fixtureDef));
}

void Collider2D::Reset() {
    rigidbody->info->body->DestroyFixture(collider->fixture);
    collider->fixture = rigidbody->info->body->CreateFixture(&(collider->fixtureDef));
}

//}

//{ #region CircleCollider2D

struct CircleCollider2D::Impl {
    b2CircleShape shape;
};

CircleCollider2D::CircleCollider2D() : info(new CircleCollider2D::Impl()) {}

void CircleCollider2D::SetShape(glm::vec2 position_, float radius_) {
    position = position_;
    radius = radius_;

    SpriteRenderer* sr = entity->GetComponent<SpriteRenderer>();
    if (sr != nullptr) {
        info->shape.m_p.Set(position_.x - sr->sprite->pivot.x * scale.x, position_.y - sr->sprite->pivot.y * scale.y);
    } else {
        info->shape.m_p.Set(position_.x, position_.y);
    }
    info->shape.m_radius = radius_ * scale.x;
    collider->fixtureDef.shape = &(info->shape);
}

void CircleCollider2D::Copy(CircleCollider2D* other) {
    if (other == nullptr) return;
    Collider2D::Copy(other);

    info->shape = other->info->shape;
    position = other->position;
    radius = other->radius;
}
void CircleCollider2D::ResetShape() {
    scale = {transform->scale.x, transform->scale.y};
    SetShape(position, radius);
}

//}

//{ #region BoxCollider2D

struct BoxCollider2D::Impl {
    b2PolygonShape shape;
};

BoxCollider2D::BoxCollider2D() : info(new BoxCollider2D::Impl()) {}

void BoxCollider2D::SetShape(glm::vec2 hsize) {
    SpriteRenderer* sr = entity->GetComponent<SpriteRenderer>();

    boxHalfSize = hsize;
    if (sr != nullptr) {
        b2Vec2 pivot(sr->sprite->pivot.x * scale.x, sr->sprite->pivot.y * scale.y);
        info->shape.SetAsBox(boxHalfSize.x * scale.x, boxHalfSize.y * scale.y, -pivot, 0.0f);
    } else {
        info->shape.SetAsBox(boxHalfSize.x * scale.x, boxHalfSize.y * scale.y);
    }
    collider->fixtureDef.shape = &(info->shape);
}

void BoxCollider2D::Copy(BoxCollider2D* other) {
    if (other == nullptr) return;
    Collider2D::Copy(other);

    info->shape = other->info->shape;
    boxHalfSize = other->boxHalfSize;
}

void BoxCollider2D::ResetShape() {
    scale = {transform->scale.x, transform->scale.y};
    SetShape(boxHalfSize);
}

//}

//{ #region EdgeCollider2D

// TODO EdgeCollider2D

//}

//{ #region PolygonCollider2D

// TODO PolygonCollider2D

//}

}  // namespace se
