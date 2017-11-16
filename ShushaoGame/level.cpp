#include "globals.h"
#include "level.h"
#include "pancrazio.h"

Level::Level() {

	AddEntity<Pancrazio>();

	SpriteRenderer* backgroundRenderer = root->AddComponent<SpriteRenderer>();
	backgroundRenderer->shader = Resources::Get<Shader>("standard");
	backgroundRenderer->name = "Background Renderer";
	backgroundRenderer->sortingLayerID = SortingLayers::BACKGROUND;
	backgroundRenderer->sprite = new Sprite("Background", Resources::Get<Texture>("night"));
	backgroundRenderer->sprite->setPixelPerUnit(64);

	/*Entity* Mario = AddEntity("Mario");
	Sprite* pancrazioSprite2 = new Sprite("Sprite di Pancrazio 2", Resources::Get<Texture>("pancsmile"));
	pancrazioSprite2->setPivot({0.0f, 16.0f});
	Mario->AddComponent<SpriteRenderer>();
	Mario->GetComponent<SpriteRenderer>()->sprite = pancrazioSprite2;
    Mario->GetComponent<SpriteRenderer>()->color = {0.0f, 1.0f, 1.0f, 1.0f};
	Mario->GetComponent<SpriteRenderer>()->shader =  Resources::Get<Shader>("standard");
	Mario->transform->localPosition.x = 5.0f;
	Mario->transform->localScale = {2.0f, 2.0f, 0.0f};*/
}

Level::~Level() {
	//
}
