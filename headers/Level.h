
#ifndef LEVEL_H
#define LEVEL_H
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

class Level {
    sf::Texture background;
    sf::Sprite backgroundSprite;
    sf::View view;
    sf::SoundBuffer buffer;
    sf::Sound music;
    sf::Clock clock;
    Ground ground;
    Player player;
    AttemptCounter attempts;
    LevelProgression levelProgression;
    std::vector<Chunk> chunks;
    std::deque<std::shared_ptr<Obstacle> > obstacles; //lista obstacolelor active
    float chunkSize=2000.0f;
    long long unsigned int currentChunkIndex=0;
    bool restartGame=false;
    float velocity=850.0f;
    // std::ifstream fin;
    std::string inputFile;
    double levelLength = 0;
    double totalDistanceTravelled = 0;
    double deltaTime=0.0f;

    double getDeltaTime();

    void updateObstacles();

    void loadChunks();

    void updateView();

    void resetLevel();

public:
    Level(const std::string &sound_buffer,const std::string &file,sf::RenderWindow &win,sf::Color levelColor);
    Level()=default;
    friend std::ostream &operator<<(std::ostream &os, const Level &level);
    void render(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void startLevelLogic();
    void stopLevel();


};

#endif //LEVEL_H