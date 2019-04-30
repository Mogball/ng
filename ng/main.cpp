#include "game.h"

using namespace ng;

int main() {
    ng::Game game;
    game.create_rect(50, 10, 0, -20, 0, b2_staticBody);
    game.create_rect(1, 1, 0, 20, 0.2);
    game.run();

    return EXIT_SUCCESS;
}
