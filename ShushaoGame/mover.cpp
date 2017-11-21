#include "mover.h"

void Mover::Awake() {

	sr = entity->GetComponent<SpriteRenderer>();
}

void Mover::Update() {


	//LOG(INFO, ts(transform->localPosition.x));

	transform->localPosition.x += 1.5f * Time::deltaTime;

	if (Time::GetTime() - animTime >= 0.1f) {
		animTime = Time::GetTime();
		sr->sprite = Resources::Get<SpriteSheet>("walking")->next();
		LOG(INFO, sr->sprite->name);
	}
}
