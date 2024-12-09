#include "../headers/Player.h"
#include <iostream>
#include <cmath>
#include "../headers/Ground.h"
#define GRAVITY 7500.0f
#define ON_GROUND 785.0f

Player::Player(float position)
: isJumping(false) , jumpSpeed(0.0f) , jumpHeight(250.0f)
{
    this->body.setSize(sf::Vector2f(100.0f, 100.0f));
    if (!this->texture.loadFromFile("images/Player.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->body.setTexture(&texture);
    body.setPosition(sf::Vector2f(350.0f, position-body.getSize().y/2.0f));
    body.setOrigin(body.getSize().x / 2.0f, body.getSize().y / 2.0f);
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


void Player::updatePlayer(const double deltaTime) {
    //aceasta functie este folosita pentru a gestiona actiunea de saritura
    //a playerului la apasarea tastei space

    //intrucat playerul nu se misca ,ci tot ce este in jurul sau se misca de la dreapta
    //la stanga , ne vom ocupa doar de miscarea playerului pe axa Oy
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& !isJumping) {
        isJumping=true;
        //7500-constanta a gravitatii ,mai mare pentru un gameplay mai apropiat de jocul
        //original
        jumpSpeed = -sqrtf(2.0f * GRAVITY * jumpHeight);
    }
    //daca sare atunci se va aplica o gravitatie care este de 2 ori mai mica decat
    //saritura playerului
    if(isJumping) {
        jumpSpeed += GRAVITY * deltaTime;
        rotationAngle += 375.0f * deltaTime;
        // rotationAngle=400.0f;
    }
    body.move(0.0f,static_cast<float>(jumpSpeed*deltaTime));
    // Normalizează unghiul pentru a rămâne între 0 și 360
    if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;

    // Aplică rotația
    body.setRotation(static_cast<float>(rotationAngle));
}
void Player::renderPlayer(sf::RenderWindow &window) {
    window.draw(body);
}

void Player::handleCollisionGround(const Ground &ground) {
    if (checkCollisionGround(ground)) {
        // this->body.setPosition(this->body.getPosition().x,ground.getBounds1().top-this->getBounds().height/2.0f);
        this->body.setPosition(this->body.getPosition().x,ground.getBounds1().top-50.0f);
        isJumping=false;
        jumpSpeed=0.0f;
        rotationAngle=calculateFallingSide(rotationAngle);
    }
}

bool Player::checkCollisionGround(const Ground &ground) const {
    return (this->body.getGlobalBounds().intersects(ground.getBounds1())
            || this->body.getGlobalBounds().intersects(ground.getBounds2()));
}
void Player::handleCollisionObstacle(bool &endGame, double deltaTime, float &velocity, const Obstacle &obstacle) {
    if (checkCollisionObstacle(obstacle)) {
        if (obstacle.getType() == ObstacleType::BLOCK || obstacle.getType() == ObstacleType::PLATFORM) {
            if (isAboveObstacle(deltaTime, obstacle)) {
                //daca intersecteaza obstac    olul pe deasupra pozitionam playerul pe obstacol
                this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height/2.0f);
                isJumping = false;
                // body.setRotation(0.0f);
                rotationAngle=calculateFallingSide(rotationAngle);
            }
            else {
                //daca jucatorul intersecteaza obiectul prin stanga
                if (isCollidingFromSides(obstacle)) {
                    //daca jucatorul intersecteaza obiectul de sus
                    if (isOnTopOfObstacle(obstacle)) {
                        if (this->body.getPosition().y < obstacle.getBounds().top) {
                            //daca se afla pe obiect
                            handleLandingOnObstacle(obstacle);
                        } else {
                            //se afla in stanga lui
                            handleLeftCollision(endGame, obstacle, velocity);
                        }
                    }
                }
            }
        }
        if (obstacle.getType() == ObstacleType::SPIKE || obstacle.getType() == ObstacleType::SPIKE_SHORT) {
            handleSpikeCollision(endGame, velocity);
        }
        if(obstacle.getType()==ObstacleType::END) {
            endGame = true;
            std::cout<<"Level completed ! Well done!\n";
        }
    }
    //else trateaza cazul in care player a cazut de pe bloc
    //daca nu exista acest else player putea sa sara in timp ce cadea ,dupa ce fusese pe un bloc
    else {
        if (fallingFromBlock(obstacle)) {
            isJumping = true;
            if (this->body.getPosition().y >= ON_GROUND) {
                //daca dupa caderea de pe bloc a ajuns eventual pe sol resetam jump
                isJumping = false;
            }
        }
    }
}

bool Player::fallingFromBlock(const Obstacle &obstacle) const {
    return ((obstacle.getType() == ObstacleType::BLOCK || obstacle.getType() == ObstacleType::PLATFORM)
            && this->body.getGlobalBounds().left > obstacle.getBounds().left +
            obstacle.getBounds().width && this->body.getGlobalBounds().top + this->body.getGlobalBounds().height
            > obstacle.getBounds().top);
}
bool Player::checkCollisionObstacle(const Obstacle &obstacle) const {
    return (this->body.getGlobalBounds().intersects(obstacle.getBounds()));
}

bool Player::isAboveObstacle(double deltaTime, const Obstacle &obstacle) const {
    return (this->getBounds().top + this->getBounds().height - jumpSpeed * deltaTime <= obstacle.getBounds().top);
//verifica daca playerul urmeaza sa intersecteze un obiect pe deasupra
}

bool Player::isCollidingFromSides(const Obstacle &obstacle) const {
    return (this->getBounds().left < obstacle.getBounds().left + obstacle.getBounds().width &&
            this->getBounds().left + this->getBounds().width > obstacle.getBounds().left);
    //verifica daca intersecteaza un obiect prin laterala
}

bool Player::isOnTopOfObstacle(const Obstacle &obstacle) const {
    return (this->getBounds().top < obstacle.getBounds().top + obstacle.getBounds().height &&
            this->getBounds().top + this->getBounds().height > obstacle.getBounds().top);
    //verifica daca intersecteaza un obiect pe verticala
}

void Player::handleLandingOnObstacle(const Obstacle &obstacle) {
    this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height/2.0f);
    isJumping = false;
}

void Player::handleLeftCollision(bool &endGame, const Obstacle &obstacle, float &velocity) {
    this->body.setPosition(obstacle.getBounds().left - this->getBounds().width, this->body.getPosition().y/2.0f);
    endGame = true;
    velocity = 0.0f;
}

void Player::handleSpikeCollision(bool &endGame, float &velocity) {
    endGame = true;
    velocity = 0.0f;
    jumpSpeed = 0.0f;
    isJumping = false;
}

//785, coord y pentru plasarea blocurilor pe podea
sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}

double Player::calculateFallingSide(double angle) {
    int side=static_cast<int>((angle+45.0f)/90)%4;
    return side*90;
}

