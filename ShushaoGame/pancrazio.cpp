#include "pancrazio.h"
#include "mover.h"

Pancrazio::Pancrazio() {

	sr = AddComponent<SpriteRenderer>();
	AddComponent<Mover>();

	sr->shader = Resources::Get<Shader>("standard");
	sr->sprite = Resources::Get<Sprite>("walking_2");//->setPivot({0.0f, 16.0f});
	sr->sortingLayerID = Config::SortingLayers["Characters"];

	transform->localScale = {1.0f, 1.0f, 0.0f};
}

Pancrazio::~Pancrazio() {

}
