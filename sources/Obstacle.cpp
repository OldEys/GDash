#include "../headers/Obstacle.h"

#include <iostream>

TextureManager Obstacle::texture_manager;

void Obstacle::updateObstacle(float velocity,double deltaTime) {
    body.move(static_cast<float>(velocity*deltaTime),0.0f);
    hitbox.move(static_cast<float>(velocity*deltaTime),0.0f);
}
void Obstacle::renderObstacle(sf::RenderWindow &window) {
    window.draw(this->body);
    // window.draw(this->hitbox);
}

void Obstacle::adjustPositionX(float offset) {
    sf::Vector2f currentPosition = this->body.getPosition();
    currentPosition.x += offset;
    this->body.setPosition(currentPosition);
    // this->hitbox.setPosition(currentPosition);
    this->hitbox.setPosition(this->body.getPosition().x
                             + this->body.getGlobalBounds().width / 2.0f,
                             this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
}

sf::Vector2f Obstacle::getPosition() const {
    return body.getPosition();
}


Obstacle::Obstacle(Obstacle &&other) noexcept:
   body(std::move(other.body)),
   hitbox(std::move(other.hitbox)),
   texture(other.texture) {
    body.setTexture(&texture);
    std::cout << "move constructor obstacle\n";
}

Obstacle &Obstacle::operator=(Obstacle &&other) noexcept {
    if (this != &other) {
        body = std::move(other.body);
        hitbox = std::move(other.hitbox);
        texture = other.texture;
        body.setTexture(&texture);

        std::cout << "Move assignment operator obstacle\n";
    }
    return *this;
}


Obstacle::Obstacle(const Obstacle& other) :
body{other.body},
hitbox{other.hitbox},
texture {other.texture}
{
body.setTexture(&texture);
}

Obstacle& Obstacle:: operator=(const Obstacle& other) {
    if (this != &other) {
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
