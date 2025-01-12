
#include"../headers/Short_Spike.h"

#include <iostream>

Short_Spike::Short_Spike(const sf::Vector2f &pos) :Obstacle("images/spike.png",sf::Vector2f(100.0f,50.0f),
                                                            sf::Color::White,sf::Color::White,0.0f,sf::Vector2f(30.0f,15.0f)) {
    this->body.setPosition(pos.x,pos.y+this->body.getGlobalBounds().height);
    this->hitbox.setPosition(this->body.getPosition().x
                              + this->body.getGlobalBounds().width / 2.0f,
                              this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
    std::cout<<"Short spike created\n";
}
void Short_Spike::onCollision(Player &player, bool &restartGame, float &velocity) {
    if(player.boundingBoxTest(this->hitbox.getPosition(),this->hitbox.getSize(),this->hitbox.getRotation()))
    {
        player.triggerDeath();
        restartGame = true;
        velocity = 0.0f;
    }
}

void Short_Spike::afis(std::ostream &os) const {
    os << "This is a short spike\n";
}
