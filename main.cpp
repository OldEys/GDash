#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include <Helper.h>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "Game.h"




int main() {
    /// NOTE: this function call is needed for environment-specific fixes //

    /// NOTE: mandatory use one of vsync or FPS limit (not both)
    Game game;
    while(game.isRunning()) {

        game.update();
        game.render();
    }
    return 0;
}
