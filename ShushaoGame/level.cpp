#include "level.h"
#include "spriterenderer.h"
#include "texture.h"
#include "sprite.h"
#include "gameobject.h"

using namespace ShushaoEngine;

Level::Level() {

	Texture* pancrazioTexture = new Texture();
	pancrazioTexture->name = "Pancrazio Texture";
	pancrazioTexture->Load("assets/pancrazio.png");

	Sprite* pancrazioSprite = new Sprite();
    pancrazioSprite->texture = pancrazioTexture;

    GameObject* Player = new GameObject();

    Player->name = "Pancrazio";

	SpriteRenderer* PlayerSR = Player->AddComponent<SpriteRenderer>();
    PlayerSR->sprite = pancrazioSprite;

    AddGameObject(Player);

}
