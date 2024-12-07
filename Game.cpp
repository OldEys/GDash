#include "Game.h"
#include <fstream>
#include <iostream>
#include <thread>

#include "env_fixes.h"
#include <mutex>
std::mutex chunkMutex;

#define MIN_DELTA_TIME_FPS 60.0f
#define ALIGN_VIEW_Y 520.0f
Game::Game() : window(nullptr),
               event{},
               endGame(false),
               firstChunk(true)
{
    this->initWindow();
    ground = Ground(*this->window);
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
    this->buffer.loadFromFile("sound/Level_soundtrack.ogg");
    this->music.setBuffer(this->buffer);
    music.play();
    this->view.setCenter(player.getPosition().x + 620.0f, player.getPosition().y - 250.0f);
    this->view.setSize(1920.0f, 1080.0f);
    this->window->setView(this->view);
    std::cout << "Game constructor\n";
    // std::thread loadingThread(&Game::loadChunks, this);
    // loadingThread.detach();
    // loadingThread.join();
    std::cout<<"incepe de incarcat\n";
    loadChunks();
    std::cout<<"gata de incarcat\n";
    chunkLoadClock.restart();
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
    this->player.updatePlayer(this->deltaTime);
    this->player.handleCollisionGround(this->ground);
    // this->totalDistanceTraveled +=10.0f*this->velocity * this->deltaTime;
    //distanta totala parcursa de player,folosita pentru a spawna la momentul potrivit
    //chunkurile jocului
    this->ground.updateGround(-this->velocity, this->deltaTime);
    this->updateObstacles();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            velocity=0.0f;
    }
    for (const auto &obstacle: this->obstacles) {
        this->player.handleCollisionObstacle(endGame, this->deltaTime, this->velocity, obstacle);
    }
    this->updateView();
    if (endGame) {
        sf::sleep(sf::microseconds(100));
        window->close();
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
    // std::lock_guard<std::mutex> lock(chunkMutex);
    std::ifstream fin("obstacole.in");
    if (!fin.is_open()) {
        std::cout << "File cant open" << std::endl;
        return;
    }
    Chunk currentChunk = Chunk(0.0f, chunkSize);
    std::string objtype;
    float x, y;
    while (fin >> objtype >> x >> y) {
        //citim si in functie de ce string citim
        //cream un obiect in chunkul curent
        if (x >= currentChunk.getStartX() && x < currentChunk.getEndX()) {
            //daca se afla in chunkul curent
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
            Obstacle obs1(sf::Vector2f(x, y), type);
            // currentChunk.addObstacle(&Obstacle(sf::Vector2f(x, y), type));
            std::cout<<"add in loadChunks cand e in int chunkului\n";
            currentChunk.addObstacle(obs1);
            std::cout<<"gata in loadChunks cand e in int chunkului\n";
        } else if(x>=currentChunk.getEndX()){
            std::cout<<"depaseste chunkul curent,se creeaza altul nou\n";
            //daca nu se afla in chunkul curent adaugam unul nou
            chunks.push_back(std::move(currentChunk));
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
                std::cout<<"se add obstacolele cand e dupa chunk\n";
                Obstacle obs1(sf::Vector2f(x, y), type);
                // currentChunk.addObstacle(&Obstacle(sf::Vector2f(x, y), type));
                currentChunk.addObstacle(obs1);
            }
        }
    }

    //la final cream ultimul chunk
    chunks.push_back(std::move(currentChunk));
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
    window->setView(view);
}
void Game::updateObstacles() {
    //motiv problema nesincronizare chunkuri
    //chunkurile nu se spawneaza la momentul potrivit ci mai tarziu
    //ce ce determina sa se miste atunci cand sunt create
    //daca nu sunt puse cand trebuie o sa se miste atunci cand sunt create
    //si o sa fie nesincronizate
    if (!chunks.empty()&&chunkLoadClock.getElapsedTime().asSeconds() >= chunkLoadInterval) {
        chunkLoadClock.restart();
        //functie de actualizat obstacolele
        while (currentChunkIndex < chunks.size()) {
            // chunks[currentChunkIndex].getStartX() <= totalDistanceTraveled + 5*window->getSize().x) ){
            //cat timp exista chunkuri si playerul a intrat in chunk
            const auto &newObstacles = chunks[currentChunkIndex].getObstacles();
            std::cout<<"se vor adauga la obj active \n";
            // obstacles.insert(obstacles.end(), newObstacles.begin(), newObstacles.end());
            obstacles.insert(obstacles.end(),std::make_move_iterator(newObstacles.begin()),
            std::make_move_iterator(newObstacles.end()));
            chunks.erase(chunks.begin() + static_cast<long long int>(currentChunkIndex));
            // currentChunkIndex++;
            std::cout<<"s-au adaugat la obj active\n";
            // chunks.erase(chunks.begin() + currentChunkIndex);
        }
        //se extrag obstacolele din chunkul in care se afla playerul
        //si se insereaza la vectorul de obstacole active
    }
    // }
    //daca un obstacol ajunge in stanga ecranului este sters din vectorul de obstacole active
    if (!obstacles.empty() && obstacles.begin()->getPosition().x < -100.0f) {
        obstacles.pop_front();
    }
    //se misca obstacolele spre stanga
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
    os << "velocity: " << game.velocity << "\n";
    os << "deltaTime: " << game.deltaTime << "\n";
    os << "Player: \n" << game.player;
    os << "ground: \n" << game.ground;
    return os;
}
