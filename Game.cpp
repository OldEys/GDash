

#include "Game.h"

#include <iostream>
#include "env_fixes.h"

Game::Game() :  window(nullptr)
// ,isAlive(true)
{
    this->initWindow();
    ground=Ground(*this->window);
    ground.initGround();
    this->background.loadFromFile("../images/background1-3.png");
    this->backgroundSprite.setTexture(this->background);
    this->backgroundSprite.setPosition(0.0f, 0.0f);
    this->backgroundSprite.setScale(
        static_cast<float>(this->window->getSize().x) / this->background.getSize().x,
        static_cast<float>(this->window->getSize().y) / this->background.getSize().y
    );
    this->backgroundSprite.setColor(sf::Color::Blue);

    // obstacles.emplace_back(Obstacle(ObstacleType::BLOCK,200.0f));
    // obstacles.push_back(Obstacle(ObstacleType::BLOCK,300.0f));
    // obstacles.push_back(Obstacle(ObstacleType::BLOCK,400.0f));
    //     this->groundTexture.loadFromFile("../images/ground-long.png");
    //     this->groundBody.setTexture(&this->groundTexture);
    //     float scaleX =static_cast<float>(this->window->getSize().x)/this->groundTexture.getSize().x;
    //     float scaleY =scaleX;
    //     this->groundBody.setSize(sf::Vector2f(static_cast<float>(this->groundTexture.getSize().x),static_cast<float>(this->groundTexture.getSize().y)));
    //     this->groundBody.setScale(scaleX,scaleY);
    //     this->groundBody.setPosition(0.0f,this->window->getSize().y-scaleY*this->groundBody.getSize().y);
    //     this->groundBody.setFillColor((sf::Color(75,75,255)));
    this->player.setPosition(ground.getGroundPos());
}
bool Game::isRunning() const {
    return this->window->isOpen();
}

void Game::initWindow()  {
    this->videoMode.width=1920;
    this->videoMode.height=1080;
    this->window = new sf::RenderWindow(this->videoMode,"GDash",sf::Style::Default);
    this->window->setPosition(sf::Vector2i(0,0));
    this->window->setFramerateLimit(144);
    this->window->setPosition(sf::Vector2i(0,0));
}

void Game::pollEvents() {
    bool shouldExit = false;
    init_threads();
    while(this->window->pollEvent(this->event)) {
        if(this->event.type == sf::Event::Closed) {
            shouldExit = true;
        }
        if(this->event.type == sf::Event::KeyPressed) {
            if(this->event.key.code == sf::Keyboard::Escape) {
                shouldExit = true;
        }
        break;
        }
    }
    if(shouldExit) {
        this->window->close();
    }
}
void Game :: update() {
    this->pollEvents();
    this->player.updatePlayer(this->getDeltaTime(),ground);
    // this->updateGround(-300.0f, this->getDeltaTime());
    this->ground.updateGround(-300.0f,this->getDeltaTime());
    //update functions
}

double Game::getDeltaTime() {
    return 1./60;
}

// void Game::updateObstacles() {
//     if(!isAlive) return ;
//
//     for(auto& obstacle : this->obstacles) {
//         obstacle.updateObstacle(-300.0f,getDeltaTime());
//     }
// }
Game::~Game() {
    delete this->window;
    std::cout<<"Game destructor"<<std::endl;
}
void Game :: render() {
    this->window->clear();
    this->window->draw(this->backgroundSprite);
    // this->window->draw(this->groundBody);
    this->ground.renderGround(*this->window);
    // for(auto& obstacle:obstacles) {
    //     obstacle.renderObstacle(*this->window);
    // }
    this->player.renderPlayer(*this->window);
    this->window->display();
}
// void Game::updateGround(float velocity,float deltaTime) {
//     this->groundBody.move(velocity*deltaTime,0.0f);
//     if(this->groundBody.getPosition().x +this->groundBody.getSize().x< 0) {
//         this->groundBody.setPosition(1920.0f,this->groundBody.getPosition().y);
//         std::cout<<"Ground body updated"<<std::endl;
//     }
// }
