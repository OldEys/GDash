#include <iostream>
#include "headers/Exceptions.h"
#include "headers/Game.h"

int main() {
    try {
        Game &game = Game::getInstanceGame();
        while (game.isRunning()) {
            game.handleEvents();
            game.update();
            game.render();
        }

    } catch (Texture_error &e) {
        std::cerr << "Texture error: " << e.what() << std::endl;
    } catch (Sound_error &e) {
        std::cerr << "Sound error: " << e.what() << std::endl;
    } catch (Font_error &e) {
        std::cerr << "Font error: " << e.what() << std::endl;
    }catch (InvalidLevelIndex_error &e) {
        std::cerr << "Index error: " << e.what() << std::endl;
    } catch (InputFile_error &e) {
        std::cerr << "File error: " << e.what() << std::endl;
    } catch (ApplicationException &e) {
        std::cerr << "Unexpected application error: " << e.what() << std::endl;
    }

    return 0;
}


// #include <iostream>
//
// #include "headers/Exceptions.h"
// #include "headers/Game.h"
// int main() {
//     try{
//         Game game;
//         while(game.isRunning()) {
//         game.update();
//         game.render();
//         }
//         // operator<<(std::cout,game);
//         // std::cout<<game;
//     } catch (Texture_error &e) {
//         std::cout << e.what() << std::endl;
//     }catch (Sound_error &e) {
//         std::cout << e.what() << std::endl;
//     }catch (Font_error &e) {
//         std::cout << e.what() << std::endl;
//     }catch (InputFile_error &e) {
//         std::cout << e.what() << std::endl;
//     }catch (ApplicationException &e) {
//         std::cerr << "Unexpected error: " << e.what() << std::endl;
//     }
//     return 0;
// }