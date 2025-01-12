#include"../headers/Platform.h"

#include <iostream>
#define ON_GROUND 785.0f

Platform::Platform(const sf::Vector2f& pos) : Obstacle("images/ground_block.png",sf::Vector2f(100.0f,40.0f),
    sf::Color(0,0,50),sf::Color::White,5.0f,sf::Vector2f(100.0f,40.0f)) {
    this->body.setPosition(pos);
    this->hitbox.setPosition(this->body.getPosition().x
                         + this->body.getGlobalBounds().width / 2.0f,
                         this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
    std::cout<<"Platform created\n";
}

// Platform::Platform(const sf::Vector2f &pos, const std::string &texturePath) {
//     this->texture=texture_manager.getTexture(texturePath);
//     this->body.setSize(sf::Vector2f(100.0f,40.0f));
//     this->body.setPosition(pos);
//     this->body.setFillColor(sf::Color(0,0,50));
//     // this->hitbox.setFillColor(sf::Color(255,0,0,50));
//     this->body.setTexture(&this->texture);
//     this->body.setOutlineColor(sf::Color::White);
//     this->body.setOutlineThickness(5.0f);
//     this->hitbox.setSize(sf::Vector2f(100.0f,40.0f));
//     this->hitbox.setOrigin(this->hitbox.getSize().x / 2.0f, this->hitbox.getSize().y / 2.0f);
//     this->hitbox.setPosition(this->body.getPosition().x
//                              + this->body.getGlobalBounds().width / 2.0f,
//                              this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
// }
void Platform::onCollision(Player &player, bool &restartGame, float &velocity) {
    if(this->hitbox.getGlobalBounds().intersects(player.getBounds())) {
        //daca jucatorul intersecteaza obiectul de sus
        if (isOnTopOfBlock(player)) {
            if (player.getPosition().y < this->hitbox.getGlobalBounds().top) {
                //daca se afla pe obiect
                // handleLandingOnObstacle(obstacle);
                player.handleLandingOnObstacle(this->hitbox.getGlobalBounds().top - player.getBounds().height / 2.0f);

            } else {
                //se afla in stanga lui
                player.triggerDeath();
                player.handleLeftCollision(restartGame, velocity);
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
bool Platform::isOnTopOfBlock(const Player &player) const {
    return (player.getBounds().top<this->hitbox.getGlobalBounds().top+
        this->hitbox.getGlobalBounds().height&&player.getBounds().top+player.getBounds().height>
    this->hitbox.getGlobalBounds().top);
}
bool Platform::fallingFromBlock(const Player& player)const {
    return ( player.getBounds().left > this->hitbox.getGlobalBounds().left +
            this->hitbox.getGlobalBounds().width && player.getBounds().top + player.getBounds().height
            > this->hitbox.getGlobalBounds().top);
}

void Platform::afis(std::ostream &os) const {
    os<<"This is a platform\n";
}
