

#include "Game.h"

#include <iostream>

#include "env_fixes.h"

Game::Game() {
    this->initWindow();
    this->background.loadFromFile("../images/background1-3.png");
    this->backgroundSprite.setTexture(this->background);
    this->backgroundSprite.setPosition(0.0f,0.0f);
    this->backgroundSprite.setScale(
    static_cast<float>(this->window->getSize().x)/this->background.getSize().x,
    static_cast<float>(this->window->getSize().y)/this->background.getSize().y
    );
    this->backgroundSprite.setColor(sf::Color::Blue);
    this->ground.loadFromFile("../images/ground-long.png");
    this->groundSprite.setTexture(this->ground);
    float scaleX =static_cast<float>(this->window->getSize().x)/this->ground.getSize().x;
    float scaleY =scaleX;
    this->groundSprite.setScale(scaleX,scaleY);
    this->groundSprite.setPosition(0.0f,this->window->getSize().y-scaleY*this->ground.getSize().y);
    this->groundSprite.setColor((sf::Color(75,75,255)));
    this->player.setPosition(this->window->getSize().y-scaleY*this->ground.getSize().y);

}
bool Game::isRunning() const {
    return this->window->isOpen();
}

void Game::initWindow() {
    // this->videoMode.height=sf::VideoMode::getDesktopMode().height;
    // this->videoMode.width=sf::VideoMode::getDesktopMode().width;
    this->videoMode.width=1920;
    this->videoMode.height=1080;
    this->window=new sf::RenderWindow(this->videoMode,"GDash",sf::Style::Default);
    this->window->setFramerateLimit(60);
    this->window->setPosition(sf::Vector2i(0,0));
}

void Game::pollEvents() {
    init_threads();
    bool shouldExit = false;
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
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(300ms);
}
void Game :: update() {
    this->pollEvents();
    //update functions
}
void Game :: render() {
    this->window->clear();
    this->window->draw(this->backgroundSprite);
    this->window->draw(this->groundSprite);
    this->player.renderPlayer(*window);
    this->window->display();
}
