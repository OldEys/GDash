#include "../headers/Block.h"

#include <iostream>
#define ON_GROUND 785.0f

Block::Block(const sf::Vector2f& pos,const std::string& texturePath) {
    this->texture=texture_manager.getTexture(texturePath);
    this->body.setSize(sf::Vector2f(100.0f,100.0f));
    this->body.setPosition(pos);
    this->body.setFillColor(sf::Color(0,0,50));
    this->body.setTexture(&this->texture);
    this->body.setOutlineColor(sf::Color::White);
    this->body.setOutlineThickness(5.0f);
    this->hitbox.setSize(sf::Vector2f(100.0f,100.0f));
    this->hitbox.setOrigin(this->hitbox.getSize().x / 2.0f, this->hitbox.getSize().y / 2.0f);
    this->hitbox.setPosition(this->body.getPosition().x
                             + this->body.getGlobalBounds().width / 2.0f,
                             this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);

}

void Block::onCollision(Player &player, bool &endGame, float &velocity) const  {
    if(this->hitbox.getGlobalBounds().intersects(player.getBounds())) {
            //daca jucatorul intersecteaza obiectul de sus
            if (isOnTopOfBlock(player)) {
                if (player.getPosition().y < this->hitbox.getGlobalBounds().top) {
                    //daca se afla pe obiect
                    // handleLandingOnObstacle(obstacle);
                    player.handleLandingOnObstacle(this->hitbox.getGlobalBounds().top -
                        this->hitbox.getGlobalBounds().height/2.0f);
                } else {
                    //se afla in stanga lui
                    player.handleLeftCollision(endGame, velocity);
                }
        }
    }
    else {
        if (fallingFromBlock(player)) {
            player.fellFromBlock(true);
            if (player.getPosition().y >= ON_GROUND) {
                //daca dupa caderea de pe bloc a ajuns eventual pe sol resetam jump
                player.fellFromBlock(false);
            }
        }
    }
}
bool Block::isOnTopOfBlock(const Player &player) const {
    return (player.getBounds().top<this->hitbox.getGlobalBounds().top+
        this->hitbox.getGlobalBounds().height&&player.getBounds().top+player.getBounds().height>
    this->hitbox.getGlobalBounds().top);
}
bool Block::fallingFromBlock(const Player& player)const {
    return ( player.getBounds().left > this->hitbox.getGlobalBounds().left +
            this->hitbox.getGlobalBounds().width && player.getBounds().top + player.getBounds().height
            > this->hitbox.getGlobalBounds().top);
}