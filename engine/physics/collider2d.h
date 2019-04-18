#pragma once

#include "../pch/math.h"
#include "../pch/physics.h"
#include "../pch/std.h"

#include "../component.h"

namespace se {

class Rigidbody2D;

class Collider2D : public Component {
public:
    virtual void setup();

    Rigidbody2D* rigidbody = nullptr;
    b2FixtureDef fixtureDef;
    b2Fixture* fixture = nullptr;

    glm::vec2 scale = {1.0f, 1.0f};

    float density = 1.0f;
    float friction = 0.3f;
    float restitution = 0.6f;

    bool isSensor = false;

    void SetDensity(float);
    void SetRestitution(float);
    void SetFriction(float);
    void SetSensor(bool);

    void Awake();
    void Start();

    void Attach();
    void Reset();

    virtual void ResetShape() {}

    void FixedUpdate();
    void OnDestroy();

    void ColliderEnter(Collider2D*);
    void ColliderExit(Collider2D*);

    void Copy(Collider2D* other) {
        if (other == nullptr) return;
        Component::Copy(other);

        scale = other->scale;
        density = other->density;
        friction = other->friction;
        restitution = other->restitution;
        isSensor = other->isSensor;
    }

protected:
    std::vector<Collider2D*> colliders;

private:
};

class PolygonCollider2D : public Collider2D {
public:
    b2PolygonShape shape;
    void SetShape(std::vector<glm::vec2>);

    void ResetShape() {}

    void Copy(PolygonCollider2D* other) {
        if (other == nullptr) return;
        Collider2D::Copy(other);

        shape = other->shape;
    }

protected:
};

class BoxCollider2D : public Collider2D {
public:
    glm::vec2 boxHalfSize;

    b2PolygonShape shape;
    void SetShape(glm::vec2);
    void ResetShape();

    void Copy(BoxCollider2D* other) {
        if (other == nullptr) return;
        Collider2D::Copy(other);

        shape = other->shape;
        boxHalfSize = other->boxHalfSize;
    }

protected:
};

class CircleCollider2D : public Collider2D {
public:
    b2CircleShape shape;
    void SetShape(glm::vec2, float);
    void ResetShape();

    void Copy(CircleCollider2D* other) {
        if (other == nullptr) return;
        Collider2D::Copy(other);

        shape = other->shape;
    }

protected:
    glm::vec2 position;
    float radius;
};

class EdgeCollider2D : public Collider2D {
public:
    b2EdgeShape shape;

    void SetShape(glm::vec2, glm::vec2);

    void ResetShape() {}

    void Copy(EdgeCollider2D* other) {
        if (other == nullptr) return;
        Collider2D::Copy(other);

        shape = other->shape;
    }

protected:
};
}  // namespace se
