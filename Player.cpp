#include "Player.h"

#include <iostream>
#include <math.h>

#include "Ground.h"

//
Player::Player()
: isJumping(false) , jumpSpeed(0.0f) , jumpHeight(250.0f)
{
    this->body.setSize(sf::Vector2f(120.0f, 120.0f));
    this->texture.loadFromFile("../images/Player.png");
    this->body.setTexture(&texture);
}



Player::~Player() {
    std::cout << "Player destroyed" << std::endl;
}

void Player::setPosition(const float position) {
    body.setPosition(sf::Vector2f(200.0f, position-body.getSize().y));
}

void Player::updatePlayer(const float deltaTime,const Ground& ground) {
    std::cout<<"deltaTime: "<<deltaTime<<std::endl;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& !isJumping) {
        isJumping=true;
        jumpSpeed=-sqrtf(2.0f*981.0f*jumpHeight);
    }
    if(isJumping)
        jumpSpeed+=981.0f*deltaTime;
    body.move(0.0f,jumpSpeed*deltaTime);
    checkCollisionGround(ground);
}

void Player::renderPlayer(sf::RenderWindow &window) {
    window.draw(body);
}

void Player::checkCollisionGround(const Ground &ground) {
    if(this->body.getGlobalBounds().intersects(ground.getBounds1())
        || this->body.getGlobalBounds().intersects(ground.getBounds2())) {
        isJumping=false;
        jumpSpeed=0;
        }
}


