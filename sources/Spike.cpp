#include"../headers/Spike.h"

#include <iostream>

Spike::Spike(const sf::Vector2f &pos) : Obstacle("images/spike.png", sf::Vector2f(100.0f, 100.0f),
                                                 sf::Color::White, sf::Color::White, 0.0f, sf::Vector2f(30.0f, 30.0f)) {
    this->body.setPosition(pos);
    this->hitbox.setPosition(this->body.getPosition().x
                             + this->body.getGlobalBounds().width / 2.0f,
                             this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
    std::cout << "Spike created\n";
}
void Spike::onCollision(Player &player, bool &endGame, float &velocity) const {
    if(player.boundingBoxTest(this->hitbox.getPosition(),this->hitbox.getSize(),this->hitbox.getRotation()))
    {
        player.triggerDeath();
        endGame = true;
        velocity = 0.0f;
    }
}
