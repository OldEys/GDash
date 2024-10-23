
#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include <chrono>
#include<thread>

#include "Ground.h"
#include "Obstacle.h"
#include "Player.h"

class Game {
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    Player player;

    // sf::Clock clock;
    // sf::Texture groundTexture;
    // sf::RectangleShape groundBody;
    Ground ground;
    // std::vector<Obstacle> obstacles;
    // bool isAlive;
public:

    Game();
    ~Game();
    bool isRunning() const;

    void initWindow();
    void pollEvents();
    void render();
    void update();
    float getDeltaTime();
    // void updateGround(float velocity,float deltaTime);
    // void updateObstacles();
};



#endif //GAME_H
