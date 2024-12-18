#include "../headers/Player.h"
#include <iostream>
#include <cmath>
#include "../headers/Ground.h"
#define GRAVITY 7500.0f

Player::Player(float position)
: isJumping(false) , jumpSpeed(0.0f) , jumpHeight(250.0f)
{
    this->body.setSize(sf::Vector2f(100.0f, 100.0f));
    if (!this->texture.loadFromFile("images/Player.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->body.setTexture(&texture);
    body.setPosition(sf::Vector2f(350.0f, position - body.getSize().y / 2.0f));
    body.setOrigin(body.getSize().x / 2.0f, body.getSize().y / 2.0f);
}

Player::Player(): isJumping(false) , jumpSpeed(0.0f) , jumpHeight(250.0f) {
    std::cout<<"constructor fara parametri\n";
}


Player::~Player() {
    std::cout << "Player destroyed" << std::endl;
}

void Player::setPosition(float x, float y) {
    this->body.setPosition(x, y);
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
    if (isJumping) {
        jumpSpeed += GRAVITY * deltaTime;
        rotationAngle += 350.0f * deltaTime;
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
        rotationAngle = calculateFallingSide(rotationAngle);
        this->body.setPosition(this->body.getPosition().x, ground.getBounds1().top - 50.0f);
        isJumping = false;
        jumpSpeed = 0.0f;
    }
}

bool Player::checkCollisionGround(const Ground &ground) const {
    return (this->body.getGlobalBounds().intersects(ground.getBounds1())
            || this->body.getGlobalBounds().intersects(ground.getBounds2()));
}
void Player::handleLandingOnObstacle(float positionY) {
    this->body.setPosition(this->body.getPosition().x, positionY);
    rotationAngle = calculateFallingSide(rotationAngle);
    isJumping = false;
}

void Player::handleLeftCollision(bool &endGame, float &velocity) {
    endGame = true;
    velocity = 0.0f;
}

//785, coord y pentru plasarea blocurilor pe podea
sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}
double Player::calculateFallingSide(double angle) {
    int side = static_cast<int>((angle + 45.0f) / 90) % 4;
    return side*90;
}

void Player::fellFromBlock(const bool &jumpState) {
    if (jumpState == false) {
        rotationAngle = calculateFallingSide(rotationAngle);
    }
    isJumping = jumpState;
}

std::array<sf::Vector2f, 4> Player::getOrientedBoundingBox() {
    sf::Transform transform;
    transform.translate(body.getPosition());
    transform.rotate(body.getRotation());

    float halfWidth = body.getSize().x / 2.f;
    float halfHeight = body.getSize().y / 2.f;

    std::array<sf::Vector2f, 4> localPoints = {
        sf::Vector2f(-halfWidth, -halfHeight),
        sf::Vector2f(halfWidth, -halfHeight),
        sf::Vector2f(halfWidth, halfHeight),
        sf::Vector2f(-halfWidth, halfHeight)
    };

    std::array<sf::Vector2f, 4> worldPoints;
    for (size_t i = 0; i < localPoints.size(); ++i) {
        worldPoints[i] = transform.transformPoint(localPoints[i]);
    }

    return worldPoints;
}

void Player::projectOntoAxis(const std::array<sf::Vector2f, 4> &points, const sf::Vector2f &axis, float &min,
                             float &max) {
    min = max = points[0].x * axis.x + points[0].y * axis.y;
    for (size_t i = 1; i < points.size(); ++i) {
        float projection = points[i].x * axis.x + points[i].y * axis.y;
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }
}

bool Player::boundingBoxTest(const sf::Vector2f &obstaclePosition, const sf::Vector2f &obstacleSize,
                             float obstacleRotation) {
    auto playerPoints = getOrientedBoundingBox();

    sf::Transform obstacleTransform;
    obstacleTransform.translate(obstaclePosition);
    obstacleTransform.rotate(obstacleRotation);

    float halfWidth = obstacleSize.x / 2.f;
    float halfHeight = obstacleSize.y / 2.f;

    std::array<sf::Vector2f, 4> obstacleLocalPoints = {
        sf::Vector2f(-halfWidth, -halfHeight),
        sf::Vector2f(halfWidth, -halfHeight),
        sf::Vector2f(halfWidth, halfHeight),
        sf::Vector2f(-halfWidth, halfHeight)
    };

    std::array<sf::Vector2f, 4> obstacleWorldPoints;
    for (size_t i = 0; i < obstacleLocalPoints.size(); ++i) {
        obstacleWorldPoints[i] = obstacleTransform.transformPoint(obstacleLocalPoints[i]);
    }

    std::array<sf::Vector2f, 4> axes = {
        playerPoints[1] - playerPoints[0],
        playerPoints[2] - playerPoints[1],
        obstacleWorldPoints[1] - obstacleWorldPoints[0],
        obstacleWorldPoints[2] - obstacleWorldPoints[1]
    };

    // Proiectează punctele pe fiecare axă
    for (const auto &axis: axes) {
        float playerMin, playerMax, obstacleMin, obstacleMax;
        projectOntoAxis(playerPoints, axis, playerMin, playerMax);
        projectOntoAxis(obstacleWorldPoints, axis, obstacleMin, obstacleMax);

        if (!(obstacleMin <= playerMax && obstacleMax >= playerMin)) {
            return false;
        }
    }

    return true;
}
