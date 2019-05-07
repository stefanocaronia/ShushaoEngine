#include <Box2D/Box2D.h>

#include "PhysicsImpl.h"
#include "Rigidbody2d.h"
#include "Shushao/Entity.h"
#include "Shushao/transform.h"

namespace se {

struct Rigidbody2D::Impl {
    b2Body* body = nullptr;
    b2BodyDef bodyDef;
};

Rigidbody2D::Rigidbody2D() : info(new Impl()) {}

void Rigidbody2D::Copy(Rigidbody2D* other) {
    if (other == nullptr) return;
    Component::Copy(other);

    position = other->position;
    velocity = other->velocity;
    angle = other->angle;
    angularVelocity = other->angularVelocity;
    fixedRotation = other->fixedRotation;
    type = other->type;  // TODO: controllare che sia copy
}

void Rigidbody2D::OnDestroy() {
    if (info->body == nullptr) return;
    Physics::impl->world->DestroyBody(info->body);
}

void Rigidbody2D::Awake() {
    position = transform->position;
    angle = transform->GetEulerAngles().z;

    /// DA CAPIRE, se devo lasciare dynamic (fa le collisioni con gli static) o no
    /*if (!transform->isAtRoot() && type == RigidbodyType::DYNAMIC) {
			type = RigidbodyType::KINEMATIC;
		}*/

    info->bodyDef.type = (b2BodyType)type;
    info->bodyDef.position.Set(position.x, position.y);
    info->bodyDef.angle = angle * DEGTORAD;  // RADIANS
    info->bodyDef.fixedRotation = fixedRotation;
    info->bodyDef.userData = this;
    info->bodyDef.active = enabled && entity->active;

    info->body = Physics::impl->world->CreateBody(&(info->bodyDef));
}

void Rigidbody2D::OnEnable() {
    info->body->SetActive(transform->isAtRoot() && entity->active);
}

void Rigidbody2D::OnDisable() {
    info->body->SetActive(false);
}

void Rigidbody2D::SetType(RigidbodyType type_) {
    type = type_;
    info->bodyDef.type = (b2BodyType)type;
    if (info->body != nullptr) {
        info->body->SetType(info->bodyDef.type);
    }
}

void Rigidbody2D::SetFixedRotation(bool fr) {
    fixedRotation = fr;
    info->bodyDef.fixedRotation = fr;
    if (info->body != nullptr) {
        info->body->SetFixedRotation(fr);
    }
}

void Rigidbody2D::Update() {
    if (transform->isAtRoot()) {
        info->body->SetActive(entity->active);
    }
}

void Rigidbody2D::FixedUpdate() {
    if (type == RigidbodyType::STATIC) {
        position = transform->position;
        angle = transform->GetEulerAngles().z;  // DEGREES
        info->body->SetTransform(b2Vec2(position.x, position.y), angle * DEGTORAD);
        return;
    }

    b2Vec2 p = info->body->GetPosition();
    b2Vec2 v = info->body->GetLinearVelocity();
    position = {p.x, p.y};
    velocity = {v.x, v.y};
    angle = info->body->GetAngle() * RADTODEG;  // DEGREES
    angularVelocity = info->body->GetAngularVelocity();

    transform->SetPosition({position.x, position.y, transform->position.z});
    transform->SetRotation({0.0f, 0.0f, angle});
}
}  // namespace se
