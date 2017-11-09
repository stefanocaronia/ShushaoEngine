#include <iostream>

#include "game.h"

using namespace ShushaoEngine;
using namespace std;

int main(int argc, char *argv[]) {

	Game Shushao("Shushao Game!");

	Shushao.init();

	Shushao.run();

	return 0;
}
