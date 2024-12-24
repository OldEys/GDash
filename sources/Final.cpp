#include"../headers/Final.h"

#include <iostream>

Final::Final(const sf::Vector2f &pos, const std::string &texturePath) {
    this->texture = texture_manager.getTexture(texturePath);
    this->body.setSize(sf::Vector2f(200.0f, 400.0f));
    this->body.setPosition(pos);
    this->body.setFillColor(sf::Color::White);
    this->body.setTexture(&this->texture);
    this->body.setOutlineColor(sf::Color::White);
    this->body.setOutlineThickness(0.0f);
    this->hitbox.setSize(sf::Vector2f(200.0f, 400.0f));
    this->hitbox.setOrigin(this->hitbox.getSize().x / 2.0f, this->hitbox.getSize().y / 2.0f);
    this->hitbox.setPosition(this->body.getPosition().x
                             + this->body.getGlobalBounds().width / 2.0f,
                             this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
}
// void Final::finalProximity(Player &player, float &velocity, double deltaTime) {
//     static bool positioned = false;
//     static float storedVel = 0.0f;
//
//     if (this->getPosition().x > 1760 && this->getPosition().x < 1800) {
//         if (!positioned) {
//             if (storedVel == 0.0f) {
//                 storedVel = velocity;
//             }
//             this->body.setPosition(1780.0f, this->getPosition().y);
//             positioned = true;
//         }
//         player.moveTowardsEnd(storedVel, deltaTime);
//         velocity = 0.0f;
//     }
// }
void Final::finalProximity(Player &player,float& velocity,double deltaTime) {
    static bool positioned=false;
    static float storedVel=0.0f;
    if(this->getPosition().x>1780 && this->getPosition().x<1820) {
        if (!positioned) {
            storedVel = velocity;
            this->body.setPosition(1800.0f, this->getPosition().y);
            positioned = true;
        }
        player.moveTowardsEnd(storedVel,deltaTime);
        velocity=0.0f;
    }
    else {
        positioned=false;
        storedVel=0.0f;
    }
}
void Final::onCollision(Player &player, bool &endGame, float &) const {
    if (this->hitbox.getGlobalBounds().intersects(player.getBounds())) {
        endGame = true;
        std::cout << "Level completed , well done!\n";
    }
}

