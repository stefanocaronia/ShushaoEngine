#include "globals.h"
#include "level.h"
#include "pancrazio.h"
#include "mover.h"

Level::Level() {

	Pancrazio* pancrazio = AddEntity<Pancrazio>();
	pancrazio->transform->setLocalScale({1.0f, 1.0f, 0.0f});
	pancrazio->transform->localPosition = {0.0f, 0.0f, 0.0f};
	//pancrazio->GetComponent<Animation>()->Disable();
	//pancrazio->transform->setLocalRotation({0,0,45});

	Pancrazio* sonOfPancrazio = AddEntity<Pancrazio>("Son of Pancrazio");
	sonOfPancrazio->setParent(pancrazio);
	sonOfPancrazio->GetComponent<Animation>()->Disable();
	sonOfPancrazio->GetComponent<Mover>()->Disable();
	sonOfPancrazio->transform->setLocalPosition({-1.0f, 0.0f, 0.0f});
	sonOfPancrazio->transform->setLocalScale({0.5f, 0.5f, 0.0f});
	//sonOfPancrazio->transform->setLocalRotation({0,0,20});

	SpriteRenderer* backgroundRenderer = root->AddComponent<SpriteRenderer>();
	backgroundRenderer->shader = Resources::Get<Shader>("standard");
	backgroundRenderer->name = "Background Renderer";
	backgroundRenderer->sortingLayerID = Config::SortingLayers["Background"];
	backgroundRenderer->sprite = new Sprite("Background", Resources::Get<Texture>("night"));
	backgroundRenderer->sprite->setPixelPerUnit(64);
}

Level::~Level() {
	//
}
