#include <iostream>

#include "libs.h"
#include "game.h"
#include "resources.h"
#include "texture.h"
#include "shader.h"
#include "asset.h"

using namespace ShushaoEngine;
using namespace std;

int main(int argc, char *argv[]) {

	Time::setFrameRateLimit(120.0f);
	Time::setFixedRateLimit(20.0f);

	//Config::displayWidth = 600;
	//Config::displayHeight = (int)(Config::displayWidth / Config::displayAspect);

	Config::Layers[1] = "Player";
	Config::Layers[2] = "Background";

	Resources::Load<Texture>("assets/pancrazio.png");
	//Resources::Load<Shader>("shaders/standard");

	//Shader* sha = new Shader();
	//return 5;

	Game Shushao("Shushao Game!");

	Shushao.init();
	Shushao.run();

	//delete(sha);

	return 0;
}
