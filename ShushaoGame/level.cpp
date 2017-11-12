#include "level.h"
#include "linerenderer.h"
#include "spriterenderer.h"
#include "texture.h"
#include "sprite.h"
#include "entity.h"
#include "resources.h"
#include "gamedata.h"
#include "debug.h"

using namespace ShushaoEngine;

Level::Level() {

	LOG(INFO, "Constructor di Scene LEVEL");

	Sprite* pancrazioSprite = new Sprite("Sprite di Pancrazio");
    pancrazioSprite->texture = Resources::Get<Texture>("pancrazio");

    pancrazioSprite->pivot = {-1.0f, 1.0f};

	Sprite* pancrazioSprite2 = new Sprite("Sprite di Pancrazio 2");
    pancrazioSprite2->texture = Resources::Get<Texture>("pancsmile");

    Entity* Pancrazio = AddEntity("Pancrazio");
    Entity* Mario = AddEntity("Mario");

	Pancrazio->AddComponent<SpriteRenderer>();
	Mario->AddComponent<SpriteRenderer>();

    Pancrazio->GetComponent<SpriteRenderer>()->sprite = pancrazioSprite;
	Pancrazio->GetComponent<SpriteRenderer>()->shader = Resources::Get<Shader>("standard");

	Mario->GetComponent<SpriteRenderer>()->sprite = pancrazioSprite2;
    Mario->GetComponent<SpriteRenderer>()->color = {0.0f, 1.0f, 1.0f, 1.0f};
	Mario->GetComponent<SpriteRenderer>()->shader =  Resources::Get<Shader>("standard");

	Mario->transform->position.x = 5.0f;
	Mario->transform->localScale = {2.0f, 2.0f, 0.0f};


}

Level::~Level() {
	//
}
