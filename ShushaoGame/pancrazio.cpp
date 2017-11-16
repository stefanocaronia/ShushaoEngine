#include "pancrazio.h"
#include "resources.h"
#include "shader.h"
#include "spriterenderer.h"
#include "mover.h"
#include "globals.h"

Pancrazio::Pancrazio() {

	sr = AddComponent<SpriteRenderer>();
	Mover* mv = AddComponent<Mover>();
	mv->enabled = true;

	sr->shader = Resources::Get<Shader>("standard");

	sr->sprite = new Sprite("Sprite di Pancrazio", Resources::Get<Texture>("pancrazio"));
	sr->sprite->setPivot({0.0f, 16.0f});

	sr->sortingLayerID = SortingLayers::CHARACTERS;

	transform->localScale = {1.0f, 1.0f, 0.0f};

}

Pancrazio::~Pancrazio() {

}
