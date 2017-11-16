#include "mover.h"
#include "debug.h"
#include "transform.h"
#include "setime.h"

void Mover::Update() {
	transform->localPosition.x += 1.5f * Time::deltaTime;
	transform->localPosition.y += 1.5f * Time::deltaTime;
	//LOG(INFO, ts(transform->localPosition.x));
}
