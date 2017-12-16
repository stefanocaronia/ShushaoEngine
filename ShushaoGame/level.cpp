#include "globals.h"
#include "level.h"
#include "pancrazio.h"
#include "mover.h"


Level::Level() {


	Entity* ground = AddEntity("Ground");

	ground->transform->setLocalPosition({0.0f, -4.0f, 0.0f});
	Rigidbody2D* groundrb = ground->AddComponent<Rigidbody2D>();
	groundrb->setType(RigidbodyType::STATIC);
	BoxCollider2D* ec = ground->AddComponent<BoxCollider2D>();
	ec->setShape({6,0.5f});

	//ground->transform->setLocalRotation({0,0,45});

	Pancrazio* pancrazio = AddEntity<Pancrazio>();
	pancrazio->transform->setLocalScale({1.0f, 1.0f, 0.0f});
	pancrazio->transform->setLocalPosition({0.0f, 0.0f, 0.0f});
	//pancrazio->GetComponent<Animation>()->Disable();
	pancrazio->transform->setLocalRotation({0,0,45});

	/*Pancrazio* sonOfPancrazio = AddEntity<Pancrazio>("Son of Pancrazio");
	sonOfPancrazio->setParent(pancrazio);
	//sonOfPancrazio->GetComponent<Animation>()->Disable();
	//sonOfPancrazio->GetComponent<Mover>()->Disable();
	sonOfPancrazio->transform->setLocalPosition({-1.0f, 0.0f, 0.0f});
	sonOfPancrazio->transform->setLocalScale({0.5f, 0.5f, 0.0f});
	sonOfPancrazio->GetComponent<BoxCollider2D>()->resetShape(); // <---- collegare al transform addirittura? fare dei callback transformChanged
	//sonOfPancrazio->transform->setLocalRotation({0,0,20});*/

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
