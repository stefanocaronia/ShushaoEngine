#pragma once

#include "../component.h"

namespace se {

enum class RigidbodyType {
    STATIC = b2_staticBody,
    KINEMATIC = b2_kinematicBody,
    DYNAMIC = b2_dynamicBody
};

class SHUSHAO_API Rigidbody2D : public Component {
public:
    virtual void setup() {
        name = "Rigidbody 2D";
    }

    glm::vec2 position = glm::vec2(0, 0);
    glm::vec2 velocity = glm::vec2(0, 0);
    float angle = 0.0f;  // DEGREES
    float angularVelocity = 0.0f;

    bool fixedRotation = false;

    void SetType(RigidbodyType type_);
    void SetFixedRotation(bool fr);
    void Copy(Rigidbody2D* other);

    void Awake();
    void Update();
    void FixedUpdate();
    void OnDestroy();
    void OnDisable();
    void OnEnable();

    struct Impl;  // Pimpl!
    std::unique_ptr<Impl> info;

private:
    RigidbodyType type = RigidbodyType::DYNAMIC;
};

}  // namespace se
