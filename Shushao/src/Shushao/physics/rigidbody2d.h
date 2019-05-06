#pragma once

#include <Box2D/Box2D.h>

#include "Shushao/Core.h"
#include "../component.h"

namespace se {

class Collider2D;

enum class RigidbodyType {
    STATIC = b2_staticBody,
    KINEMATIC = b2_kinematicBody,
    DYNAMIC = b2_dynamicBody
};

class SHUSHAO_API Rigidbody2D : public Component {
public:
    virtual void setup() { name = "Rigidbody 2D"; }

    b2Body* body = nullptr;

    glm::vec2 position = glm::vec2(0, 0);
    glm::vec2 velocity = glm::vec2(0, 0);
    float angle = 0.0f;  // DEGREES
    float angularVelocity = 0.0f;

    bool fixedRotation = false;

    void SetType(RigidbodyType type_) {
        type = type_;
        bodyDef.type = (b2BodyType)type;
        if (body != nullptr) body->SetType(bodyDef.type);
    }

    void SetFixedRotation(bool fr) {
        fixedRotation = fr;
        bodyDef.fixedRotation = fr;
        if (body != nullptr) body->SetFixedRotation(fr);
    }

    void Copy(Rigidbody2D* other);

    void Awake();
    void Update();
    void FixedUpdate();
    void OnDestroy();
    void OnDisable();
    void OnEnable();

private:
    b2BodyDef bodyDef;
    RigidbodyType type = RigidbodyType::DYNAMIC;
};

}  // namespace se
