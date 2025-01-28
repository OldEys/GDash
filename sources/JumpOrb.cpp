#include"../headers/JumpOrb.h"
#include <iostream>

JumpOrb::JumpOrb(const sf::Vector2f &pos) : Obstacle("images/JumpOrb.png", sf::Vector2f(100.0f, 100.0f),
                                                     sf::Color::White, sf::Color::White, 0.0f,
                                                     sf::Vector2f(100.0f, 100.0f)) {
    this->body.setPosition(pos);
    this->hitbox.setPosition(this->body.getPosition().x
                             + this->body.getGlobalBounds().width / 2.0f,
                             this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
}

void JumpOrb::afis(std::ostream &os) const {
    os << "This is a jumporb";
}

PlayerStatChanges JumpOrb::onCollisionImplem(Player &player) {
    if (this->hitbox.getGlobalBounds().intersects(player.getBounds())) {
        static bool mouseheld = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (!mouseheld) {
                mouseheld = true;
                return {
                        {"isJumping", false},
                };
            }
        } else {
            mouseheld = false;
        }
    }

    return {};
}
