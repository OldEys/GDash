#include "Player.h"

#include <iostream>
//
Player::Player() {
    this->body.setSize(sf::Vector2f(120.0f, 120.0f));
    this->texture.loadFromFile("../images/Player.png");
    this->sprite.setTexture(texture);
    this->sprite.setScale(
        this->body.getSize().x/this->texture.getSize().x,
        this->body.getSize().y/this->texture.getSize().y);
    this->sprite.setPosition(this->body.getPosition().x,this->body.getPosition().y);
}


Player::~Player() {
    std::cout << "Player destroyed" << std::endl;
}

void Player::setPosition(float position) {
    body.setPosition(sf::Vector2f(200.0f, position-body.getSize().y));
    sprite.setPosition(body.getPosition());
}

void Player::updatePlayer() {
}

void Player::renderPlayer(sf::RenderWindow &window) {
    window.draw(body);
    window.draw(sprite);
}

