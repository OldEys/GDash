//
// Created by Babii Victor on 10/20/2024.
//

#include "Obstacle.h"

#include <iostream>

Obstacle::Obstacle(ObstacleType type,sf::Vector2f position) {
    this->type = type;
    this->body.setPosition(position);
    if(this->type== ObstacleType::BLOCK) {
        if(!this->texture.loadFromFile("../images/ground_block.png")) {
            std::cout<<"Error loading ground block texture\n";
        }
        else
            std::cout<<"Ground block texture loaded successfully\n";
        body.setSize(sf::Vector2f(100.0f,100.0f));
        body.setTexture(&this->texture);
        this->body.setFillColor(sf::Color(0,0,50));
        this->body.setOutlineColor(sf::Color::White);
        this->body.setOutlineThickness(4.0f);

        this->hitbox.setSize(sf::Vector2f(100.0f,100.0f));
        this->hitbox.setPosition(this->body.getPosition());
        this->body.setOutlineColor(sf::Color::White);
        this->body.setOutlineThickness(5.0f);
    }
    if(this->type== ObstacleType::PLATFORM) {
        if(!this->texture.loadFromFile("../images/ground_block.png")) {
            std::cout<<"Error loading ground block texture\n";
        }
        else
            std::cout<<"platform texture loaded successfully\n";
        body.setSize(sf::Vector2f(100.0f,40.0f));
        body.setTexture(&this->texture);
        this->body.setFillColor(sf::Color(0,0,50));
        this->body.setOutlineColor(sf::Color::White);
        this->body.setOutlineThickness(4.0f);

        this->hitbox.setSize(sf::Vector2f(100.0f,50.0f));
        this->hitbox.setPosition(this->body.getPosition());
        this->body.setOutlineColor(sf::Color::White);
        this->body.setOutlineThickness(5.0f);
    }
    if(this->type== ObstacleType::SPIKE) {
        if(!this->texture.loadFromFile("../images/spike.png")) {
            std::cout<<"Error loading ground block texture\n";
        }
        else
            std::cout<<"spike texture loaded successfully\n";
        body.setSize(sf::Vector2f(100.0f,100.0f));
        body.setTexture(&this->texture);
        this->hitbox.setSize(sf::Vector2f(30.0f,30.0f));
        this->hitbox.setPosition(this->body.getPosition().x+35.0f,this->body.getPosition().y+35.0f);
    }
    if(this->type== ObstacleType::SPIKE_SHORT) {
        if(!this->texture.loadFromFile("../images/spike.png")) {
            std::cout<<"Error loading ground block texture\n";
        }
        else
            std::cout<<"short texture loaded successfully\n";
        body.setSize(sf::Vector2f(100.0f,50.0f));
        body.setTexture(&this->texture);
        this->hitbox.setSize(sf::Vector2f(30.0f,15.0f));
        body.setPosition(body.getPosition().x, this->body.getPosition().y+body.getGlobalBounds().height);
        this->hitbox.setPosition(this->body.getPosition().x+40.0f,this->body.getPosition().y+40.0f);
    }
}
void Obstacle::updateObstacle(float velocity,float deltaTime) {
    body.move(velocity*deltaTime,0.0f);
    hitbox.move(velocity*deltaTime,0.0f);
}
void Obstacle::renderObstacle(sf::RenderWindow &window) {
    window.draw(this->body);
}

sf::Vector2f Obstacle::getPosition() const {
    return hitbox.getPosition();
}

const sf::FloatRect Obstacle::getBounds() const {
    return hitbox.getGlobalBounds();
}

ObstacleType Obstacle::getType() const {
    return type;
}

Obstacle::Obstacle(const Obstacle& other) {
    type = other.type;
    body = other.body;
    hitbox = other.hitbox;
    texture = other.texture;
    body.setTexture(&texture);
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

