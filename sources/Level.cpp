#include "../headers/Game.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>

#include "../headers/Exceptions.h"
#include "../headers/ObstacleFactory.h"
#define MIN_DELTA_TIME_FPS 60.0f
#define ALIGN_VIEW_Y 520.0f

Level::Level(const std::string &song_buffer, const std::string &file, sf::RenderWindow &win, sf::Color levelColor)
    : ground(win, levelColor), player(ground.getGroundPos()), inputFile(file) {
    if (!background.loadFromFile("images/background1-3.png")) {
        throw Texture_error("images/background1-3.png");
    }
    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(
        static_cast<float>(win.getSize().x) / static_cast<float>(background.getSize().x),
        static_cast<float>(win.getSize().y) / static_cast<float>(background.getSize().y)
    );
    backgroundSprite.setColor(levelColor);
    if (!buffer.loadFromFile(song_buffer)) {
        throw Texture_error(song_buffer);
    }
    music.setBuffer(buffer);

    view.setCenter(player.getPosition().x + 620.0f, player.getPosition().y - 250.0f);
    view.setSize(1920.0f, 1080.0f);
}

void Level::startLevelLogic() {
    totalDistanceTravelled = 0.0f;
    velocity = 850.0f;
    music.play();
    this->loadChunks();
}

void Level::stopLevel() {
    music.stop();
    this->obstacles.clear();
    this->chunks.clear();
    this->totalDistanceTravelled = 0.0f;
    this->velocity = 850.0f;
}


bool isPaused = false;

void Level::update(sf::RenderWindow &window) {
    if (restartGame) {
        music.stop();
        if (player.getState()) {
            return;
        }
        this->resetLevel();
        updateObstacles();
    } else {
        this->deltaTime = std::min(getDeltaTime(), 1. / MIN_DELTA_TIME_FPS);
        this->player.updatePlayer(this->deltaTime);
        this->player.handleCollisionGround(this->ground);
        this->totalDistanceTravelled += this->velocity * this->deltaTime;
        this->ground.updateGround(-this->velocity, this->deltaTime);
        this->updateObstacles();
        this->attempts.update_position(-this->velocity, this->deltaTime);
        this->levelProgression.updatePercent(totalDistanceTravelled,
                                             levelLength + 1920.0f - player.getPosition().x - player.getBounds().width);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            if (isPaused) {
                isPaused = false;
                velocity = 850.0f;
            } else {
                isPaused = true;
                velocity = 0.0f;
            }
        }

        for (const auto &obstacle: this->obstacles) {
            obstacle->onCollision(player, restartGame, velocity);
            if (auto obs = std::dynamic_pointer_cast<Final>(obstacle)) {
                obs->finalProximity(player, velocity, deltaTime);
                obs->closeGame(window);
            }
        }
        this->updateView();
    }
}

double Level::getDeltaTime() {
    return this->clock.restart().asSeconds();
}

void Level::loadChunks() {
    //functie de a incarca toate obiectele din fisierul obstacole1.in
    //in chunkuri cu chunksize de 2000 de pixeli
    //in obstacole1.in obiectele trebuie sa fie asezate crescator
    //in functie de coordonata x din cauza modului in care
    //este gestionat vectorul de obiecte active
    std::ifstream fin(inputFile);
    if (!fin.is_open()) {
        throw InputFile_error("Error opening obstacle input file");
    }
    ObstacleFactory obstacleFactory;
    Chunk currentChunk(0.0f, chunkSize);
    std::string objType;
    float x, y;

    while (fin >> objType >> x >> y) {
        if (objType == "final") {
            levelLength = x;
        }
        sf::Vector2f pos(x, y);
        if (x >= currentChunk.getStartX() && x < currentChunk.getEndX()) {
            auto obstacle = obstacleFactory.createObstacle(objType, pos);
            if (obstacle) {
                currentChunk.addObstacle(obstacle);
            }
        } else if (x >= currentChunk.getEndX()) {
            chunks.emplace_back(std::move(currentChunk));
            Chunk nChunk(currentChunk.getEndX(), chunkSize);
            currentChunk = nChunk;
            auto obstacle = obstacleFactory.createObstacle(objType, pos);
            if (obstacle) {
                // std::cout << "se adauga obstacol in chunkul nou\n";
                currentChunk.addObstacle(obstacle);
            }
        }
    }
    chunks.emplace_back(std::move(currentChunk));
    fin.close();
}

void Level::updateView() {
    //daca jucatorul este indeajuns de sus camera urmareste pozitia jucatorului altfel are
    //o pozitie fixa
    float targetY = player.getPosition().y < 300.0f ? player.getPosition().y : ALIGN_VIEW_Y;
    sf::Vector2f currentCenter = view.getCenter();
    float lerpFactor = 0.02f;
    //reactualizam centrul si folosim lerpFactor pentru a atenua miscarea dintre
    //centrul vechi si cel nou
    float newCenterY = currentCenter.y + lerpFactor * (targetY - currentCenter.y);
    view.setCenter(currentCenter.x, newCenterY);
}

void Level::resetLevel() {
    this->totalDistanceTravelled = 0.0f;
    velocity = 850.0f;
    this->chunks.clear();
    this->loadChunks();
    this->restartGame = false;

    attempts.update_attempts_number();
    attempts.resetPosition(sf::Vector2f(500.0f, 300.0f));

    this->obstacles.clear();
    currentChunkIndex = 0;
    music.play();
}

void Level::updateObstacles() {
    if (currentChunkIndex < chunks.size() && totalDistanceTravelled >= chunks[currentChunkIndex].getStartX()) {
        const auto &chunk = chunks[currentChunkIndex];
        auto newObstacles = chunk.getObstacles();

        for (auto &obstacle: newObstacles) {
            obstacle->adjustPositionX(-chunk.getStartX() + 1920.0f);
        }
        // std::cout << "se iau obst si se insereaza in vect de obs active\n";
        obstacles.insert(obstacles.end(), std::make_move_iterator(newObstacles.begin()),
                         std::make_move_iterator(newObstacles.end()));
        // std::cout << "gata de inserat in vect de obs active\n";
        chunks.erase(chunks.begin() + static_cast<long long>(currentChunkIndex));
    }
    if (!obstacles.empty() && obstacles.front()->getPosition().x < -100.0f) {
        obstacles.pop_front();
    }

    for (auto &obstacle: obstacles) {
        obstacle->updateObstacle(-velocity, deltaTime);
    }
}


void Level::render(sf::RenderWindow &window) {
    window.setView(view);
    window.draw(this->backgroundSprite);
    ground.renderGround(window);
    for (auto &obstacle: obstacles) {
        obstacle->renderObstacle(window);
    }
    this->player.renderPlayer(window);
    player.handleDeath(deltaTime, window);
    this->attempts.render(window);
    window.setView(window.getDefaultView());
    this->levelProgression.render(window);
    window.setView(view);
}

std::ostream &operator<<(std::ostream &os, const Level &level) {
    os << "Level objects number: " << level.obstacles.size() << "\n";
    for (const auto &obstacle: level.obstacles) {
        os << "obstacle : " << *obstacle << "\n";
    }
    os << "velocity: " << level.velocity << "\n";
    os << "deltaTime: " << level.deltaTime << "\n";
    os << "Player: \n" << level.player;
    os << "ground: \n" << level.ground;
    return os;
}
