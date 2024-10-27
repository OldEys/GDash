#include "Player.h"

#include <iostream>
#include <math.h>

#include "Ground.h"

//
Player::Player(float position)
: isJumping(false) , jumpSpeed(0.0f) , jumpHeight(250.0f)
{
    this->body.setSize(sf::Vector2f(100.0f, 100.0f));
    if(!this->texture.loadFromFile("../images/Player.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->body.setTexture(&texture);
    body.setPosition(sf::Vector2f(350.0f, position-body.getSize().y));
}



Player::~Player() {
    std::cout << "Player destroyed" << std::endl;
}

Player::Player(const Player &other)
: body(other.body),
  texture(other.texture),
  isJumping(other.isJumping),
  jumpSpeed(other.jumpSpeed),
  jumpHeight(other.jumpHeight) {
    std::cout<<"copy constructor"<<std::endl;
}

Player & Player::operator=(const Player &other)
{
    if (this == &other)
        return *this;
    body = other.body;
    texture = other.texture;
    isJumping = other.isJumping;
    jumpSpeed = other.jumpSpeed;
    jumpHeight = other.jumpHeight;
    body.setTexture(&texture);
    std::cout<<"operator= de atribuire Player\n";
    return *this;
}

sf::Vector2f Player::getPosition() const {
    return body.getPosition();
}


void Player::updatePlayer(const double deltaTime,const Ground& ground) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& !isJumping) {
        isJumping=true;
        jumpSpeed=-sqrtf(2.0f*7500.0f*jumpHeight);
    }
    if(isJumping)
        jumpSpeed+=7500.0f*deltaTime;
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

// void Player::checkCollisionObstacle(float &velocity, const Obstacle &obstacle) {
//     if(this->getBounds().intersects(obstacle.getBounds())) {
//         if(obstacle.getType()==ObstacleType::SPIKE) {
//             velocity=0.0f;
//             jumpSpeed=0.0f;
//         }
//         else if(obstacle.getType()==ObstacleType::BLOCK) {
//             if(this->getBounds().top<=obstacle.getBounds().top) {
//                 this->body.setPosition(this->body.getPosition().x,obstacle.getPosition().y-this->body.getGlobalBounds().height);
//                 isJumping=false;
//             }
//             else {
//                 velocity=0.0f;
//                 jumpSpeed=0.0f;
//             }
//         }
//     }
// }
void Player::checkCollisionObstacle(float deltaTime, float &velocity, const Obstacle &obstacle) {
    if (this->getBounds().intersects(obstacle.getBounds())) {
        if (obstacle.getType() == ObstacleType::BLOCK || obstacle.getType() == ObstacleType::PLATFORM) {
            if (this->getBounds().top + this->getBounds().height - jumpSpeed * deltaTime <= obstacle.getBounds().top) {
                this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height);
                isJumping = false;
            }
            else {
                if (this->getBounds().left < obstacle.getBounds().left + obstacle.getBounds().width &&
                    this->getBounds().left + this->getBounds().width > obstacle.getBounds().left) {
                    //daca jucatorul intersecteaza obiectul prin stanga
                    if (this->getBounds().top < obstacle.getBounds().top + obstacle.getBounds().height &&
                        this->getBounds().top + this->getBounds().height > obstacle.getBounds().top) {
                        //daca jucatorul intersecteaza obiectul de sus
                        if (this->body.getPosition().y < obstacle.getBounds().top) {
                            //daca se afla pe obiect
                            this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height);
                            isJumping = false;
                        } else {
                            //se afla in stanga lui
                            this->body.setPosition(obstacle.getBounds().left - this->getBounds().width, this->body.getPosition().y);
                            velocity = 0.0f;
                        }
                    }
                }
            }
        }
        if (obstacle.getType() == ObstacleType::SPIKE || obstacle.getType() == ObstacleType::SPIKE_SHORT) {
            velocity = 0.0f;
            jumpSpeed = 0.0f;
            isJumping = false;
        }
    }
}

//790, coord y pentru plasarea blocurilor pe podea
sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}