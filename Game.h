
#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include <chrono>
#include<thread>

#include "Player.h"

class Game {
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    Player player;
    sf::Texture ground;
    sf::Sprite groundSprite;
    sf::RectangleShape groundBody;

public:

    Game();
    ~Game()=default;

    bool isRunning() const;

    void initWindow();
    void pollEvents();
    void render();
    void update();
};



#endif //GAME_H
