#include "pancrazio.h"
#include "mover.h"

Pancrazio::Pancrazio() {

	using namespace glm;

	sr = AddComponent<SpriteRenderer>();
	AddComponent<Mover>();

	sr->shader = Resources::Get<Shader>("standard");
	sr->sprite = Resources::Get<Sprite>("pancrazio_sprite")->setPivot(PivotPosition::BOTTOM);
	sr->sortingLayerID = Config::SortingLayers["Characters"];

	animation = AddComponent<Animation>("walk");
	animation->addLayer("sprite")->setTarget(sr->sprite)->load(Resources::Get<SpriteSheet>("walking"));
	animation->addLayer("color")->setTarget(transform->localScale)->load({
																			{1.0f, 1.0f, 0.0f},
																			{1.1f, 1.1f, 0.0f},
																			{1.2f, 1.2f, 0.0f},
																			{1.1f, 1.1f, 0.0f}
																		});
	animation->setStartState(AnimationState::PLAY);

	transform->localScale = {1.0f, 1.0f, 0.0f};
}

Pancrazio::~Pancrazio() {

}
