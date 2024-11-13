//
// Created by Babii Victor on 10/20/2024.
//

#include "Obstacle.h"

#include <iostream>

Obstacle::Obstacle(sf::Vector2f position, ObstacleType type)
    : type(type) {
    this->body.setPosition(position);
    switch (type) {
        case ObstacleType::BLOCK:
            this->initializeObstacle("images/ground_block.png", sf::Vector2f(100.0f, 100.0f)
                                     , sf::Vector2f(100.0f, 100.0f), sf::Color(0, 0, 50), 5.0f);
            this->hitbox.setPosition(this->body.getPosition());
            break;
        case ObstacleType::SPIKE:
            this->initializeObstacle("images/spike.png", sf::Vector2f(100.0f, 100.0f)
                                     , sf::Vector2f(30.0f, 30.0f), sf::Color::White, .0f);
            this->hitbox.setPosition(this->body.getPosition().x + 35.0f, this->body.getPosition().y + 35.0f);
            break;
        case ObstacleType::PLATFORM:
            this->initializeObstacle("images/ground_block.png", sf::Vector2f(100.0f, 40.0f)
                                     , sf::Vector2f(100.0f, 40.0f), sf::Color(0, 0, 50), 5.0f);
            this->hitbox.setPosition((this->body.getPosition()));
            break;
        case ObstacleType::SPIKE_SHORT:
            this->initializeObstacle("images/spike.png", sf::Vector2f(100.0f, 50.0f)
                                     , sf::Vector2f(30.0f, 15.0f), sf::Color::White, .0f);
            body.setPosition(body.getPosition().x, this->body.getPosition().y + body.getGlobalBounds().height);
            this->hitbox.setPosition(this->body.getPosition().x + 35.0f, this->body.getPosition().y + 25.0f);
            break;
        case ObstacleType::END:
            this->initializeObstacle("images/end.png", sf::Vector2f(200.0f, 400.0f)
                                     , sf::Vector2f(200.0f, 400.0f), sf::Color::White, 4.0f);
            this->hitbox.setPosition(this->body.getPosition());
            break;
    }
    if (this->type == ObstacleType::END) {
        if (!this->texture.loadFromFile("images/end.png")) {
            std::cout << "Error loading end texture\n";
        } else
            std::cout << "end texture loaded successfully\n";
        body.setSize(sf::Vector2f(200.0f, 400.0f));
        body.setTexture(&this->texture);
        this->hitbox.setSize(sf::Vector2f(200.0f, 400.0f));
        this->hitbox.setPosition(this->body.getPosition().x, this->body.getPosition().y);
        this->body.setOutlineThickness(4.0f);
    }
}
void Obstacle::initializeObstacle(const std::string &texturePath, sf::Vector2f bodySize, sf::Vector2f hitboxSize,
                                  sf::Color fillColor, float outlineThickness) {
    if (!this->texture.loadFromFile(texturePath)) {
        std::cout << "Error loading obstacle texture from : " << texturePath << "\n";
    } else {
        std::cout << "obstacle texture loaded successfully from : " << texturePath << "\n";
    }
    this->body.setSize(sf::Vector2f(bodySize));
    this->body.setTexture(&this->texture);
    this->body.setFillColor(fillColor);
    this->body.setOutlineColor(sf::Color::White);
    this->body.setOutlineThickness(outlineThickness);

    this->hitbox.setSize(sf::Vector2f(hitboxSize));
}
void Obstacle::updateObstacle(float velocity,double deltaTime) {
    body.move(static_cast<float>(velocity*deltaTime),0.0f);
    hitbox.move(static_cast<float>(velocity*deltaTime),0.0f);
}
void Obstacle::renderObstacle(sf::RenderWindow &window) {
    window.draw(this->body);
}

sf::Vector2f Obstacle::getPosition() const {
    return hitbox.getPosition();
}

sf::FloatRect Obstacle::getBounds() const {
    return hitbox.getGlobalBounds();
}

ObstacleType Obstacle::getType() const {
    return type;
}

Obstacle::Obstacle(const Obstacle& other) :
body{other.body},
hitbox{other.hitbox},
texture {other.texture},
type{other.type}
{
body.setTexture(&texture);
   std::cout<<"copy constructor obstacle\n";
}

Obstacle& Obstacle:: operator=(const Obstacle& other) {
    if (this != &other) {
        type = other.type;
        body = other.body;
        hitbox = other.hitbox;
        texture = other.texture;
        body.setTexture(&texture);
    }
    return *this;
}

std::ostream & operator<<(std::ostream &os, const Obstacle &obstacle) {
    os<<"position x: "<<obstacle.getPosition().x<<" y : "<<obstacle.getPosition().y<<"\n";
    os<<"size x: "<<obstacle.body.getSize().x<<" y: "<<obstacle.body.getSize().y<<"\n";
    os<<"hitbox size x: "<<obstacle.hitbox.getSize().x<<" y: "<<obstacle.hitbox.getSize().y<<"\n";
    return os;
}
