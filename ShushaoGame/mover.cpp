#include "mover.h"

void Mover::Awake() {

	sr = entity->GetComponent<SpriteRenderer>();
}

void Mover::Update() {

	//LOG(INFO, ts(transform->localPosition.x));

	transform->localPosition.x += 1.5f * Time::deltaTime;

	if (transform->localPosition.x > 8.0f) {
		if (entity->GetComponent<Animation>("walk") != nullptr)
			entity->GetComponent<Animation>("walk")->stop();
		Disable();
	}
}
