#include "Player.h"
#include <iostream>
#include <cmath>
#include "Ground.h"

Player::Player(float position)
: isJumping(false) , jumpSpeed(0.0f) , jumpHeight(250.0f)
{
    this->body.setSize(sf::Vector2f(100.0f, 100.0f));
    if (!this->texture.loadFromFile("images/Player.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->body.setTexture(&texture);
    body.setPosition(sf::Vector2f(350.0f, position-body.getSize().y));
}

Player::Player(): isJumping(false) , jumpSpeed(0.0f) , jumpHeight(250.0f) {
    std::cout<<"constructor fara parametri\n";
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
    //aceasta functie este folosita pentru a gestiona actiunea de saritura
    //a playerului la apasarea tastei space

    //intrucat playerul nu se misca ,ci tot ce este in jurul sau se misca de la dreapta
    //la stanga , ne vom ocupa doar de miscarea playerului pe axa Oy
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& !isJumping) {
        isJumping=true;
        //7500-constanta a gravitatii ,mai mare pentru un gameplay mai apropiat de jocul
        //original
        jumpSpeed=-sqrtf(2.0f*7500.0f*jumpHeight);
    }
    //daca sare atunci se va aplica o gravitatie care este de 2 ori mai mica decat
    //saritura playerului
    if(isJumping)
        jumpSpeed+=7500.0f*deltaTime;
    body.move(0.0f,static_cast<float>(jumpSpeed*deltaTime));
    handleCollisionGround(ground);
}
void Player::renderPlayer(sf::RenderWindow &window) {
    window.draw(body);
}

void Player::handleCollisionGround(const Ground &ground) {
    if (checkCollisionGround(ground)) {
        this->body.setPosition(this->body.getPosition().x,ground.getBounds1().top-this->body.getGlobalBounds().height);
        isJumping=false;
        jumpSpeed=0;
        }
}

bool Player::checkCollisionGround(const Ground &ground) const {
    return(this->body.getGlobalBounds().intersects(ground.getBounds1())
        || this->body.getGlobalBounds().intersects(ground.getBounds2()));
}

void Player::handleCollisionObstacle(bool& endGame,double deltaTime, float &velocity, const Obstacle &obstacle) {
    if (checkCollisionObstacle(obstacle)) {
        if (obstacle.getType() == ObstacleType::BLOCK || obstacle.getType() == ObstacleType::PLATFORM) {
            // if (this->getBounds().top + this->getBounds().height - jumpSpeed * deltaTime <= obstacle.getBounds().top) {
            if(isAboveObstacle(deltaTime,obstacle))
            {
                this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height);
                isJumping = false;
            }
            else {
                // // if (this->getBounds().left < obstacle.getBounds().left + obstacle.getBounds().width &&
                //     this->getBounds().left + this->getBounds().width > obstacle.getBounds().left) {
                    //daca jucatorul intersecteaza obiectul prin stanga
                if(isCollidingFromLeft(obstacle)){
                // if (this->getBounds().top < obstacle.getBounds().top + obstacle.getBounds().height &&
                //         this->getBounds().top + this->getBounds().height > obstacle.getBounds().top) {
                        //daca jucatorul intersecteaza obiectul de sus
                if(isOnTopOfObstacle(obstacle)){
                    if (this->body.getPosition().y < obstacle.getBounds().top) {
                            //daca se afla pe obiect
                            // this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height);
                            // isJumping = false;
                        handleLandingOnObstacle(obstacle);
                        } else {
                            //se afla in stanga lui

                            // this->body.setPosition(obstacle.getBounds().left - this->getBounds().width, this->body.getPosition().y);
                            // endGame=true;
                            // velocity = 0.0f;
                            handleLeftCollision(endGame,obstacle,velocity);
                        }
                    }
                }
            }
        }
        if (obstacle.getType() == ObstacleType::SPIKE || obstacle.getType() == ObstacleType::SPIKE_SHORT) {
            // endGame=true;
            // velocity = 0.0f;
            // jumpSpeed = 0.0f;
            // isJumping = false;
            handleSpikeCollision(endGame,velocity);
        }
        if(obstacle.getType()==ObstacleType::END) {
            endGame = true;
            std::cout<<"Level completed ! Well done!\n";
        }
    }
}

bool Player::checkCollisionObstacle(const Obstacle &obstacle) const {
    return (this->body.getGlobalBounds().intersects(obstacle.getBounds()));
}

bool Player::isAboveObstacle(double deltaTime, const Obstacle &obstacle) const {
    return (this->getBounds().top + this->getBounds().height - jumpSpeed * deltaTime <= obstacle.getBounds().top);
}

bool Player::isCollidingFromLeft(const Obstacle &obstacle) const {
    return(this->getBounds().left < obstacle.getBounds().left + obstacle.getBounds().width &&
                this->getBounds().left + this->getBounds().width > obstacle.getBounds().left);
}

bool Player::isOnTopOfObstacle(const Obstacle &obstacle) const {
    return (this->getBounds().top < obstacle.getBounds().top + obstacle.getBounds().height &&
                this->getBounds().top + this->getBounds().height > obstacle.getBounds().top);
}

void Player::handleLandingOnObstacle(const Obstacle &obstacle) {
    this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height);
    isJumping = false;
}

void Player::handleLeftCollision(bool& endGame, const Obstacle &obstacle, float& velocity) {
    this->body.setPosition(obstacle.getBounds().left - this->getBounds().width, this->body.getPosition().y);
    endGame=true;
    velocity = 0.0f;
}

void Player::handleSpikeCollision(bool& endGame, float& velocity) {
    endGame=true;
    velocity = 0.0f;
    jumpSpeed = 0.0f;
    isJumping = false;
}

//790, coord y pentru plasarea blocurilor pe podea
sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}

