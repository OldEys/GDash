
#ifndef GAME_H
#define GAME_H
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Chunk.h"
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
    sf::View view;
    sf::SoundBuffer buffer;
    sf::Sound music;
    sf::Clock clock;
    sf::Clock chunkLoadClock;
    float chunkLoadInterval = 1.0f;
    Ground ground;
    std::vector<Chunk> chunks;
    std::deque<Obstacle> obstacles; //lista obstacolelor active
    float chunkSize=2000.0f;
    long long unsigned int currentChunkIndex=0;
    bool endGame;
    float velocity=850.0f;

    double totalDistanceTravelled=0;
    double deltaTime=0.0f;
    bool firstChunk;

public:

    Game();
    ~Game();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
    bool isRunning() const;
    void initWindow();
    void pollEvents();
    void render();
    void update();
    double getDeltaTime();
    void updateObstacles();
    void loadChunks();

    void loadNextChunk();

    void updateView();

};

#endif //GAME_H
