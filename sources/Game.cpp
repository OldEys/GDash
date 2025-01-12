#include "../headers/Game.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <thread>

#include "../env_fixes.h"
#include "../headers/Block.h"
#include "../headers/Exceptions.h"
#include "../headers/Platform.h"
#include "../headers/Short_Spike.h"
#include "../headers/Spike.h"
#include "../headers/Final.h"
#include "../headers/JumpOrb.h"
#define MIN_DELTA_TIME_FPS 60.0f
#define ALIGN_VIEW_Y 520.0f
Game::Game() : window(nullptr),
               restartGame(false) {
    this->initWindow();
    if (!this->background.loadFromFile("images/background1-3.png")) {
        throw Texture_error("images/background1-3.png");
    }
    if (!this->buffer.loadFromFile("sound/Level_soundtrack.ogg")) {
        throw Texture_error("sound/Level_soundtrack.ogg");
    }
    ground = Ground(*this->window);
    player = Player(ground.getGroundPos());
    this->backgroundSprite.setTexture(this->background);
    this->backgroundSprite.setPosition(0.0f, 0.0f);
    //setam scala pentru spriteul backgroundului pentru a acoperi intreg windowul
    this->backgroundSprite.setScale(
        static_cast<float>(this->window->getSize().x) / static_cast<float>(this->background.getSize().x),
        static_cast<float>(this->window->getSize().y) / static_cast<float>(this->background.getSize().y)
    );
    this->backgroundSprite.setColor(sf::Color::Blue);

    this->music.setBuffer(this->buffer);
    this->view.setCenter(player.getPosition().x + 620.0f, player.getPosition().y - 250.0f);
    this->view.setSize(1920.0f, 1080.0f);
    this->window->setView(this->view);
    this->loadChunks();
    music.play();
}
bool Game::isRunning() const {
    return this->window->isOpen();
}
void Game::initWindow() {
    sf::VideoMode videoMode(1920, 1080);
    //rezolutie de 1920/1080px
    this->window = new sf::RenderWindow(videoMode, "GDash", sf::Style::Default);
    this->window->setPosition(sf::Vector2i(0, 0));
    this->window->setFramerateLimit(MIN_DELTA_TIME_FPS);
    this->window->setPosition(sf::Vector2i(0, 0));
}

void Game::pollEvents() {
    bool shouldExit = false;
    init_threads();
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            shouldExit = true;
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                shouldExit = true;
            }
            break;
        }
    }
    if (shouldExit) {
        this->window->close();
    }
}
bool isPaused = false;
void Game::update() {
    this->pollEvents();
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
            obstacle->nviOnCollision(player, restartGame, this->velocity);

            if (auto obs = std::dynamic_pointer_cast<Final>(obstacle)) {
                obs->finalProximity(player, velocity, deltaTime);
                obs->closeGame(*window);
            }
        }
        this->updateView();
    }
}

double Game::getDeltaTime() {
    return this->clock.restart().asSeconds();
}
void Game::loadChunks() {
    //functie de a incarca toate obiectele din fisierul obstacole.in
    //in chunkuri cu chunksize de 2000 de pixeli
    //in obstacole.in obiectele trebuie sa fie asezate crescator
    //in functie de coordonata x din cauza modului in care
    //este gestionat vectorul de obiecte active
    std::ifstream fin("obstacole.in");
    if (!fin.is_open()) {
        throw InputFile_error("Error opening obstacle input file");
    }
    std::map<std::string, std::function<std::shared_ptr<Obstacle>(sf::Vector2f)> > obstacleFactory =
    {
        {std::string("block"), [](sf::Vector2f pos) { return Block(pos).clone(); }},
        {std::string("spike"), [](sf::Vector2f pos) { return Spike(pos).clone(); }},
        {std::string("platform"), [](sf::Vector2f pos) { return Platform(pos).clone(); }},
        {std::string("short"), [](sf::Vector2f pos) { return Short_Spike(pos).clone(); }},
        {std::string("jumporb"), [](sf::Vector2f pos) { return JumpOrb(pos).clone(); }},
        {std::string("final"), [](sf::Vector2f pos) { return Final(pos).clone(); }}
    };
    Chunk currentChunk(0.0f, chunkSize);
    std::string objType;
    float x, y;

    while (fin >> objType >> x >> y) {
        if (objType == "final") {
            levelLength=x;
        }
        sf::Vector2f pos(x, y);
        if (x >= currentChunk.getStartX() && x < currentChunk.getEndX()) {
            if (obstacleFactory.find(objType) != obstacleFactory.end()) {
                std::cout << "se add obst in current chunk\n";
                currentChunk.addObstacle(obstacleFactory[objType](pos));
            } else {
                std::cerr << "Cant recognize object!\n";
            }
        } else if (x >= currentChunk.getEndX()) {
            chunks.emplace_back(std::move(currentChunk));
            Chunk nChunk(currentChunk.getEndX(), chunkSize);
            currentChunk = nChunk;
            if (obstacleFactory.find(objType) != obstacleFactory.end()) {
                std::cout << "se add obst in chunkul nou\n";
                currentChunk.addObstacle(obstacleFactory[objType](pos));
            } else {
                std::cerr << "Cant recognize object!\n";
            }
        }
    }
    chunks.emplace_back(std::move(currentChunk));
    fin.close();
}
void Game::updateView() {
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

void Game::resetLevel() {
    this->totalDistanceTravelled = 0.0f;
    velocity = 850.0f;
    this->chunks.clear();
    this->loadChunks();
    player.fellFromBlock(true);
    this->restartGame = false;

    attempts.update_attempts_number();
    attempts.resetPosition(sf::Vector2f(500.0f, 300.0f));

    this->obstacles.clear();
    currentChunkIndex = 0;
    music.play();
}

//problema : obstacolele se misca doar
// atunci cand sunt in vectorul de obstacole active adica si daca am introduce
// la timp un obiect indepartat din nivel tot ar fi problema deoarece el va fi
// spawnat la pozitia
// indicata de citire ,apoi se va misca la stanga insa asta este foarte intarziat pentru
//chunkul anterior ,ceea ce inseamna ca nu s ar alinia nici daca am
//citi dupa inceputul nivelului

//idee
/*misca startul la chunkuri si cand ajung la un anumit punct iei obiectele din el si
 le bagi in vectorul de obstacole active

sau

atunci cand scoatem newObstacles din chunkul nou scadem totaldistance travelled apoi le introducem
in vectorul de obst active

alta idee
in chunk nu memora un obiect pe care sa l copiezi ci doar
ce e nevoie sa cunoastem despre el(poz,tipul) deoarece
obiectele din chunkuri nu sunt folosite pana nu sunt
bagate in vectorul de obst active

*/
void Game::updateObstacles() {
    if (currentChunkIndex < chunks.size() && totalDistanceTravelled >= chunks[currentChunkIndex].getStartX()) {
        const auto &chunk = chunks[currentChunkIndex];
        auto newObstacles = chunk.getObstacles();

        for (auto &obstacle: newObstacles) {
            obstacle->adjustPositionX(-chunk.getStartX() + 1920.0f);
        }
        std::cout << "se iau obst si se insereaza in vect de obs active\n";
        obstacles.insert(obstacles.end(), std::make_move_iterator(newObstacles.begin()),
                         std::make_move_iterator(newObstacles.end()));
        std::cout << "gata de inserat in vect de obs active\n";
        chunks.erase(chunks.begin() + static_cast<long long>(currentChunkIndex));
    }
    if (!obstacles.empty() && obstacles.front()->getPosition().x < -100.0f) {
        obstacles.pop_front();
    }

    for (auto &obstacle : obstacles) {
        obstacle->updateObstacle(-velocity, deltaTime);
    }
}

Game::~Game() {
    std::cout << "destroyed game\n";
}

void Game::render() {
    window->setView(view);
    this->window->clear();
    this->window->draw(this->backgroundSprite);
    this->ground.renderGround(*this->window);
    this->player.renderPlayer(*this->window);
    player.handleDeath(deltaTime,*window);
    for (auto &obstacle: obstacles) {
        obstacle->renderObstacle(*this->window);
    }
    this->attempts.render(*this->window);
    window->setView(window->getDefaultView());
    this->levelProgression.render(*this->window);
    window->setView(view);
    this->window->display();


}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "Game Objects number: " << game.obstacles.size() << "\n";
    for (const auto &obstacle: game.obstacles) {
        os << "obstacle : " << *obstacle << "\n";
    }
    os << "velocity: " << game.velocity << "\n";
    os << "deltaTime: " << game.deltaTime << "\n";
    os << "Player: \n" << game.player;
    os << "ground: \n" << game.ground;
    return os;
}
