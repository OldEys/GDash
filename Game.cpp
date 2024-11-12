#include "Game.h"
#include <fstream>
#include <iostream>
#include "env_fixes.h"
#define MIN_DELTA_TIME_FPS 60.0f

Game::Game() : window(nullptr),
               event{},
               endGame{false}
               // ,isAlive(true)
               , totalDistanceTraveled(0.0f) {
    this->initWindow();
    ground = Ground(*this->window);
    // ground.initGround();
    player = Player(ground.getGroundPos());
    this->background.loadFromFile("images/background1-3.png");
    this->backgroundSprite.setTexture(this->background);
    this->backgroundSprite.setPosition(0.0f, 0.0f);
    //setam scala pentru spriteul backgroundului pentru a acoperi intreg windowul
    this->backgroundSprite.setScale(
        static_cast<float>(this->window->getSize().x) / static_cast<float>(this->background.getSize().x),
        static_cast<float>(this->window->getSize().y) / static_cast<float>(this->background.getSize().y)
    );
    this->backgroundSprite.setColor(sf::Color::Blue);
    this->buffer.loadFromFile("sound/level_soundtrack.ogg");
    this->music.setBuffer(this->buffer);
    music.play();
    this->view.setCenter(player.getPosition().x + 620.0f, player.getPosition().y - 250.0f);
    this->view.setSize(1920.0f, 1080.0f);
    this->window->setView(this->view);
    std::cout << "Game constructor\n";
    this->loadChunks();
}

bool Game::isRunning() const {
    return this->window->isOpen();
}

void Game::initWindow() {
    this->videoMode.width = 1920;
    this->videoMode.height = 1080;
    //rezolutie de 1920/1080px
    this->window = new sf::RenderWindow(this->videoMode, "GDash", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(0, 0));
    this->window->setFramerateLimit(MIN_DELTA_TIME_FPS);
    // this->window->setFramerateLimit(144);
    this->window->setPosition(sf::Vector2i(0, 0));
}

void Game::pollEvents() {
    bool shouldExit = false;
    init_threads();
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::Closed) {
            shouldExit = true;
        }
        if (this->event.type == sf::Event::KeyPressed) {
            if (this->event.key.code == sf::Keyboard::Escape) {
                shouldExit = true;
            }
            break;
        }
    }
    if (shouldExit) {
        this->window->close();
    }
}

void Game::update() {
    //functie de update,apelata in main in loopul principal al jocului
    this->pollEvents();
    this->deltaTime = std::min(getDeltaTime(), 1. / MIN_DELTA_TIME_FPS);
    // this->deltaTime=std::min(getDeltaTime(),1./144.f);
    this->player.updatePlayer(this->deltaTime, ground);
    this->totalDistanceTraveled += 10.0f * this->velocity * this->deltaTime;
    //distanta totala parcursa de player,folosita pentru a spawna la momentul potrivit
    //chunkurile jocului
    this->ground.updateGround(-this->velocity, this->deltaTime);
    this->updateObstacles();
    for (const auto &obstacle: this->obstacles) {
        this->player.handleCollisionObstacle(endGame, this->deltaTime, this->velocity, obstacle);
    }
    this->updateView();
    if (endGame) {
        // loadChunks();
        window->close();
    }
}

double Game::getDeltaTime() {
    return this->clock.restart().asSeconds();
}

void Game::loadChunks() {
    std::ifstream fin("obstacole.in");
    if (!fin.is_open()) {
        std::cout << "File cant open" << std::endl;
        return;
    }
    Chunk currentChunk = Chunk(0.0f, chunkSize);
    std::string objtype;
    float x, y;
    while (fin >> objtype >> x >> y) {
        if (x >= currentChunk.getStartX() && x < currentChunk.getEndX()) {
            // ObstacleType type=(objtype=="block")?ObstacleType::BLOCK :ObstacleType::SPIKE;
            ObstacleType type;
            if (objtype == "block")
                type = ObstacleType::BLOCK;
            else if (objtype == "spike")
                type = ObstacleType::SPIKE;
            else if (objtype == "short")
                type = ObstacleType::SPIKE_SHORT;
            else if (objtype == "platform")
                type = ObstacleType::PLATFORM;
            else if (objtype == "end")
                type = ObstacleType::END;
            else
                continue;
            currentChunk.addObstacle(Obstacle(sf::Vector2f(x, y), type));
        } else {
            chunks.push_back(currentChunk);
            currentChunk = Chunk(currentChunk.getEndX(), chunkSize);
            if (x >= currentChunk.getStartX() && x < currentChunk.getEndX()) {
                ObstacleType type;
                if (objtype == "block")
                    type = ObstacleType::BLOCK;
                else if (objtype == "spike")
                    type = ObstacleType::SPIKE;
                else if (objtype == "short")
                    type = ObstacleType::SPIKE_SHORT;
                else if (objtype == "platform")
                    type = ObstacleType::PLATFORM;
                else if (objtype == "end")
                    type = ObstacleType::END;
                else
                    continue;
                currentChunk.addObstacle(Obstacle(sf::Vector2f(x, y), type));
            }
        }
    }
    chunks.push_back(currentChunk);
    fin.close();
}

// void Game::updateView() {
//     if(player.getPosition().y<300.0f) {
//         view.setCenter(player.getPosition());
//     }
// }
void Game::updateView() {
    float targetY = player.getPosition().y < 300.0f ? player.getPosition().y : 520.0f;
    sf::Vector2f currentCenter = view.getCenter();
    float lerpFactor = 0.02f;
    float newCenterY = currentCenter.y + lerpFactor * (targetY - currentCenter.y);
    view.setCenter(currentCenter.x, newCenterY);
    window->setView(view);
}

void Game::updateObstacles() {
    while (currentChunkIndex < chunks.size() &&
           chunks[currentChunkIndex].getStartX() - totalDistanceTraveled < window->getSize().x) {
        const auto &newObstacles = chunks[currentChunkIndex].getObstacles();
        obstacles.insert(obstacles.end(), newObstacles.begin(), newObstacles.end());
        currentChunkIndex++;
    }

    if (!obstacles.empty() && obstacles.begin()->getPosition().x < 0) {
        obstacles.erase(obstacles.begin());
    }
    // this->checkCollision();
    for (auto &obstacle: obstacles) {
        obstacle.updateObstacle(-velocity, deltaTime);
    }
}

Game::~Game() {
    std::cout << "destroyed game\n";
}

void Game::render() {
    this->window->clear();
    this->window->draw(this->backgroundSprite);
    // this->window->draw(this->groundBody);
    this->ground.renderGround(*this->window);
    for (auto &obstacle: obstacles) {
        obstacle.renderObstacle(*this->window);
    }
    this->player.renderPlayer(*this->window);
    this->window->display();
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "Game Objects number: " << game.obstacles.size() << "\n";
    for (const auto &obstacle: game.obstacles) {
        os << "obstacle : " << obstacle << "\n";
    }
    os << "total distance travelled" << game.totalDistanceTraveled << "\n";
    os << "velocity: " << game.velocity << "\n";
    os << "deltaTime: " << game.deltaTime << "\n";
    os << "Player: \n" << game.player;
    os << "ground: \n" << game.ground;
    return os;
}
