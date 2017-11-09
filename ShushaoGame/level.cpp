#include "level.h"
#include "spriterenderer.h"
#include "texture.h"
#include "sprite.h"
#include "entity.h"
#include "resources.h"
#include "gamedata.h"

using namespace ShushaoEngine;

Level::Level() {

	Sprite* pancrazioSprite = new Sprite("Sprite di Pancrazio");
    pancrazioSprite->texture = Resources::Get<Texture>("pancrazio");

    pancrazioSprite->pivot = {0.0f,0.0f};

	Sprite* pancrazioSprite2 = new Sprite("Sprite di Pancrazio 2");
    pancrazioSprite2->texture = Resources::Get<Texture>("pancsmile");

    Entity* Pancrazio = AddEntity("Pancrazio");
    Entity* Mario = AddEntity("Mario");

	SpriteRenderer* PancrazioSR = Pancrazio->AddComponent<SpriteRenderer>();
	SpriteRenderer* MarioSR = Mario->AddComponent<SpriteRenderer>();

    PancrazioSR->sprite = pancrazioSprite;
    PancrazioSR->shader = Resources::Get<Shader>("standard");

    MarioSR->sprite = pancrazioSprite2;
    MarioSR->color = {0.0f, 1.0f, 1.0f, 1.0f};
	MarioSR->shader =  Resources::Get<Shader>("standard");

	Mario->transform->position.x = 3.0f;
	Mario->transform->localScale = {2.0f, 2.0f, 0.0f};

}

Level::~Level() {
	// eliminare qui oggetti creati
}
