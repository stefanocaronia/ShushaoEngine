#include "mover.h"

#include "gtx/string_cast.hpp"

void Mover::Awake() {

	sr = entity->GetComponent<SpriteRenderer>();

}

void Mover::Update() {

	//LOG(INFO, ts(transform->localPosition.x));

	float rotationSpeed = 0.2f;

	//transform->localPosition.x += 1.5f * Time::deltaTime;
	//transform->localPosition.y -= 0.5f * Time::deltaTime;

	Transform* son = transform->getChild(0);

	cout << "LOCAL:" << glm::to_string(transform->localPosition) << " WORLD:" << glm::to_string(transform->position) << endl;
	if (son != nullptr) {

		cout << "SON __> LOCAL:" << glm::to_string(son->localPosition) << " WORLD:" << glm::to_string(son->position) << endl;

	}


	//cout << "\r" << glm::to_string(transform->localPosition) << " " << glm::to_string(transform->position);


	//transform->setLocalRotation({0,0, transform->getLocalEulerAngles().z + Time::deltaTime * rotationSpeed});

	//cout << "\r" << glm::to_string(transform->getLocalEulerAngles());

	if (transform->localPosition.x > 8.0f) {
		if (entity->GetComponent<Animation>("walk") != nullptr)
			entity->GetComponent<Animation>("walk")->stop();
		Disable();
	}
}
