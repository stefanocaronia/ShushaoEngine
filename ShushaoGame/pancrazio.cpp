#include "pancrazio.h"
#include "mover.h"

Pancrazio::Pancrazio() {

	using namespace glm;

	sr = AddComponent<SpriteRenderer>();
	//sr->shader = Resources::Get<Shader>("standard");
	sr->sprite = Resources::Get<Sprite>("pancrazio_sprite")->setPivot(PivotPosition::CENTER);
	sr->sortingLayerID = Config::SortingLayers["Characters"];

	AddComponent<Mover>();

	rb = AddComponent<Rigidbody2D>();
	//rb->setType(RigidbodyType::KINEMATIC);
	//rb->setFixedRotation(true);
	collider = AddComponent<BoxCollider2D>();
	collider->SetShape({0.5f, 0.5f});

	BoxCollider2D* trigger = AddComponent<BoxCollider2D>();
	trigger->SetSensor(true);
	trigger->SetShape({1.5f, 0.1f});

	circlec = AddComponent<CircleCollider2D>();
	circlec->SetShape({0.0f, 0.0f}, 1.0f);


	/*animation = AddComponent<Animation>("walk");
	animation->setFPS(1);
	animation->setLoop(false);
	animation->addLayer("sprite")->setTarget(sr->sprite)->load(Resources::Get<SpriteSheet>("walking"));
	animation->addLayer("size")->setTarget(transform->localScale)->load({
		{1.0f, 1.0f, 0.0f},
		{1.1f, 1.1f, 0.0f},
		{1.2f, 1.2f, 0.0f},
		{1.3f, 1.3f, 0.0f}
	});

	animation->setStartState(AnimationState::PLAY);
	transform->localScale = {1.0f, 1.0f, 0.0f};*/
}

Pancrazio::~Pancrazio() {

}


