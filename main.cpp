#include <iostream>

#include "headers/Exceptions.h"
#include "headers/Game.h"
int main() {
    Game game;
    while(game.isRunning()) {

    game.update();
    game.render();
    }
    operator<<(std::cout,game);
    return 0;
}
