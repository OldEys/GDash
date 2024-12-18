
#include"../headers/Short_Spike.h"

Short_Spike::Short_Spike(const sf::Vector2f &pos, const std::string &texturePath) {
    this->texture=texture_manager.getTexture(texturePath);
    this->body.setSize(sf::Vector2f(100.0f,50.0f));
    this->body.setPosition(pos.x,pos.y+this->body.getGlobalBounds().height);
    this->body.setFillColor(sf::Color::White);
    this->body.setTexture(&this->texture);
    this->body.setOutlineColor(sf::Color::White);
    this->body.setOutlineThickness(0.0f);
    this->hitbox.setSize(sf::Vector2f(30.0f,15.0f));
    this->hitbox.setOrigin(this->hitbox.getSize().x / 2.0f, this->hitbox.getSize().y / 2.0f);
    this->hitbox.setPosition(this->body.getPosition().x
                             + this->body.getGlobalBounds().width / 2.0f,
                             this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);

}
void Short_Spike::onCollision(Player &player, bool &endGame, float &velocity) const {
    if(player.boundingBoxTest(this->hitbox.getPosition(),this->hitbox.getSize(),this->hitbox.getRotation()))
    {
        endGame = true;
        velocity = 0.0f;
    }
}
