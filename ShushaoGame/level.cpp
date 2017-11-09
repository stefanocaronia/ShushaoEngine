#include "level.h"
#include "spriterenderer.h"
#include "texture.h"
#include "sprite.h"
#include "gameobject.h"
#include "resources.h"
#include "gamedata.h"

using namespace ShushaoEngine;

Level::Level() {

	/*Texture* pancrazioTexture = new Texture();
	pancrazioTexture->name = "Pancrazio Texture";
	pancrazioTexture->Load("assets/pancrazio.png");

	Sprite* pancrazioSprite = new Sprite();
    pancrazioSprite->texture = pancrazioTexture;*/

	Sprite* pancrazioSprite = new Sprite();
    pancrazioSprite->texture = Resources::Get<Texture>("pancrazio");

    cout << pancrazioSprite->texture->name;

    GameObject* Player = AddGameObject("Pancrazio");

    //Player->name = "Pancrazio";

	/*SpriteRenderer* PlayerSR = Player->AddComponent<SpriteRenderer>();
    PlayerSR->sprite = pancrazioSprite;

	PlayerSR->shader = Resources::Get<Shader>("standard");
	cout << "playerSR shader: " << PlayerSR->shader->name;*/

}
