#include"../headers/Final.h"
#include <iostream>

Final::Final(const sf::Vector2f& pos) : Obstacle("images/final.png",sf::Vector2f(400.0f,890.0f),
                                                 sf::Color::White, sf::Color::White, 0.0f,
                                                 sf::Vector2f(200.0f, 890.0f)), endGame(false) {
    this->body.setPosition(pos);
    this->hitbox.setPosition(this->body.getPosition().x
                         + this->body.getGlobalBounds().width / 2.0f,
                         this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
    std::cout<<"Final created\n";
}

// Final::Final(const sf::Vector2f &pos, const std::string &texturePath) {
//     this->texture = texture_manager.getTexture(texturePath);
//     this->body.setSize(sf::Vector2f(400.0f, 890.0f));
//     this->body.setPosition(pos);
//     this->body.setFillColor(sf::Color::White);
//     this->body.setTexture(&this->texture);
//     this->body.setOutlineColor(sf::Color::White);
//     this->body.setOutlineThickness(0.0f);
//     this->hitbox.setSize(sf::Vector2f(200.0f, 890.0f));
//     this->hitbox.setOrigin(this->hitbox.getSize().x / 2.0f, this->hitbox.getSize().y / 2.0f);
//     this->hitbox.setPosition(this->body.getPosition().x
//                              + this->body.getGlobalBounds().width / 2.0f,
//                              this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
// }
void Final::finalProximity(Player &player, float &velocity, double deltaTime) {
    static bool positioned = false;
    //daca playerul se apropie de final atunci tot ce se misca spre stanga se opreste iar playerul
    //care de obicei statea pe loc incepe sa se miste inspre dreapta pentru a crea efectul
    //de intrat in portal

    static float storedVel = 0.0f;
    if (this->getPosition().x > 1700 && this->getPosition().x < 1740) {
        if (!positioned) {
            //daca nu e pozitionat portalul final il pozitionam
            //astfel incat sa fie exact in dreapta ecranului
            storedVel = velocity;
            this->body.setPosition(1720.0f, this->getPosition().y);
            positioned = true;
        }
        player.moveTowardsEnd(storedVel, deltaTime);
        velocity = 0.0f;
    } else {
        positioned = false;
        storedVel = 0.0f;
    }
}

void Final::closeGame(sf::RenderWindow &window) {
    if(endGame)
        window.close();
}

PlayerStatChanges Final::onCollisionImplem(Player &player) {
    if (this->hitbox.getGlobalBounds().intersects(player.getBounds())) {
        endGame = true;
        std::cout << "Level completed , well done!\n";
    }
    return {};
}


void Final::afis(std::ostream &os) const {
    os<<"This is an end portal\n";
}
