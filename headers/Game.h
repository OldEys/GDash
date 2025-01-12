
#ifndef GAME_H
#define GAME_H
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "AttemptCounter.h"
#include "Chunk.h"
#include "Ground.h"
#include "LevelProgression.h"
#include "Obstacle.h"
#include "Player.h"

class Game {
    sf::RenderWindow *window;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    Player player;
    sf::View view;
    sf::SoundBuffer buffer;
    sf::Sound music;
    sf::Clock clock;
    Ground ground;
    AttemptCounter attempts;
    LevelProgression levelProgression;
    std::vector<Chunk> chunks;
    std::deque<std::shared_ptr<Obstacle> > obstacles; //lista obstacolelor active
    float chunkSize=2000.0f;
    long long unsigned int currentChunkIndex=0;
    bool restartGame;
    float velocity=850.0f;

    double levelLength = 0;
    double totalDistanceTravelled = 0;
    double deltaTime=0.0f;

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

    void updateView();

    void resetLevel();
};

#endif //GAME_H
