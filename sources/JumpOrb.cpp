#include"../headers/JumpOrb.h"
#include <iostream>

JumpOrb::JumpOrb(const sf::Vector2f &pos) : Obstacle("images/JumpOrb.png", sf::Vector2f(100.0f, 100.0f),
                                                     sf::Color::White, sf::Color::White, 0.0f, sf::Vector2f(100.0f, 100.0f)){
    this->body.setPosition(pos);
    this->hitbox.setPosition(this->body.getPosition().x
                             + this->body.getGlobalBounds().width / 2.0f,
                             this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
    std::cout<<"JumpOrb created"<<std::endl;
}

void JumpOrb::afis(std::ostream &os) const {
    os<<"This is a jumporb";
}

void JumpOrb::onCollision(Player &player, bool &, float &) {
    if(this->hitbox.getGlobalBounds().intersects(player.getBounds())) {
        player.handleJumpOrbCollision();
        // player.fellFromBlock(false);
    }
}
