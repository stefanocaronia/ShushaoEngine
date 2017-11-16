#include "mover.h"

void Mover::Update() {


	//LOG(INFO, ts(transform->localPosition.x));

	if (transform->localPosition.x > 3.0f) {
		transform->localPosition.y -= 1.5f * Time::deltaTime;
	} else {
		transform->localPosition.x += 1.5f * Time::deltaTime;
		transform->localPosition.y += 1.5f * Time::deltaTime;
	}
}
