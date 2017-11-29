#include "mover.h"

#include "glm/gtx/string_cast.hpp"

void Mover::Awake() {

	sr = entity->GetComponent<SpriteRenderer>();

}

void Mover::Update() {

	float rotationSpeed = 0.2f;

	transform->localPosition.x += 1.5f * Time::deltaTime;

	Transform* son = transform->getChild(0);

	transform->setLocalRotation({0,0, transform->getLocalEulerAngles().z + Time::deltaTime * rotationSpeed});

	if (transform->localPosition.x > 8.0f) {
		if (entity->GetComponent<Animation>("walk") != nullptr)
			entity->GetComponent<Animation>("walk")->stop();
		Disable();
	}
}
