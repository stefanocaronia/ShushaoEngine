#include <iostream>

#include "libs.h"
#include "game.h"

using namespace ShushaoEngine;
using namespace std;

int main(int argc, char *argv[]) {

	Time::setFrameRateLimit(120.0f);
	Time::setFixedRateLimit(20.0f);

	Game Shushao("Shushao Game!");

	Shushao.init();
	Shushao.run();

	return 0;
}
