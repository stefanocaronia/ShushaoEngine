#include <iostream>
#include <sstream>

#include "game.h"
#include "debug.h"
#include "utility.h"

using namespace ShushaoEngine;
using namespace std;

int main(int argc, char *argv[]) {


	Game Shushao("Shushao Game!");

	Shushao.init();
	Shushao.run();

	return 0;
}
