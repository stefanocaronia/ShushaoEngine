#include "game.h"

int main(int argc, char *argv[]) {
    Game Shushao;

    if (Shushao.init())
        Shushao.run();

    return 0;
}
