#include "game.h"

int main(int argc, char *argv[]) {

	Game Shushao("Shushao Game!");

	/* auto data = se::Resources::GetEmbeddedData(STANDARDSHADER_VERT);
	auto txt = std::string(data.begin(), data.end());

	std::cout << txt << endl;

	return 0; */

	if (Shushao.init())
		Shushao.run();

	return 0;
}
