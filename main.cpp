#include <iostream>

#include "headers/Exceptions.h"
#include "headers/Game.h"
int main() {
    try{
        Game game;
        while(game.isRunning()) {
            game.update();
            game.render();
        }
        // operator<<(std::cout,game);
        std::cout<<game;
    } catch (Texture_error &e) {
        std::cout << e.what() << std::endl;
    }catch (Sound_error &e) {
        std::cout << e.what() << std::endl;
    }catch (Font_error &e) {
        std::cout << e.what() << std::endl;
    }catch (InputFile_error &e) {
        std::cout << e.what() << std::endl;
    }catch (ApplicationException &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    return 0;
}
