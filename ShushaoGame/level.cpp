#include "level.h"
#include "spriterenderer.h"
#include "texture.h"
#include "sprite.h"
#include "gameobject.h"
#include "resources.h"

using namespace ShushaoEngine;

Level::Level() {

	Texture* pancrazioTexture = new Texture();
	pancrazioTexture->name = "Pancrazio Texture";
	pancrazioTexture->Load("assets/pancrazio.png");

	Sprite* pancrazioSprite = new Sprite();
    pancrazioSprite->texture = pancrazioTexture;

	/*Sprite* pancrazioSprite = new Sprite();
    pancrazioSprite->texture = Resources::Get<Texture>("pancrazio");*/

    GameObject* Player = new GameObject();

    Player->name = "Pancrazio";

	SpriteRenderer* PlayerSR = Player->AddComponent<SpriteRenderer>();
    PlayerSR->sprite = pancrazioSprite;


	//PlayerSR->shader = Resources::Get<Shader>("standard");
    //PlayerSR->shader = new Shader("shaders/standard");

    AddGameObject(Player);

}
