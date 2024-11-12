#include <iostream>

#include "Game.h"
int main() {
    Game game;
    while(game.isRunning()) {

        game.update();
        game.render();
    }
    // operator<<(std::cout,game);
    std::cout << game;
    return 0;
}
