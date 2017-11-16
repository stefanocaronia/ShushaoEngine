#include "shushaoengine.h"
#include "game.h"

int main(int argc, char *argv[]) {

	Game Shushao("Shushao Game!");

	if (Shushao.init())
		Shushao.run();

	return 0;
}
