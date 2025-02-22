#include "../headers/Player.h"
#include <iostream>
#include <cmath>

#include "../headers/Exceptions.h"
#include "../headers/Ground.h"
#define GRAVITY 7500.0f

Player::Player(float position)
: stats{0.0, false, 0.0f, 0.0f}, isDead(false), jumpHeight(250.0f) {
if (!this->texture.loadFromFile("images/Player.png")) {
    throw Texture_error("images/Player.png");
}
if (!this->death_buffer.loadFromFile("sound/death_sound.ogg")) {
    throw Sound_error("sound/death_sound.ogg");
}
this->body.setSize(sf::Vector2f(100.0f, 100.0f));
    this->body.setTexture(&texture);
    body.setPosition(sf::Vector2f(350.0f, position - body.getSize().y / 2.0f));
    body.setOrigin(body.getSize().x / 2.0f, body.getSize().y / 2.0f);
    this->death_sound.setBuffer(this->death_buffer);
    this->death_sound.setVolume(100);
}

Player::Player(): stats{0.0, false, 0.0f, 0.0f}, isDead(false), jumpHeight(250.0f) {
}



void Player::setPosition(float x, float y) {
    this->body.setPosition(x, y);
}

Player::Player(const Player &other)
: body(other.body),
  texture(other.texture),
  stats{other.stats},
  isDead(other.isDead),
  jumpHeight(other.jumpHeight) {
body.setTexture(&texture);
death_sound.setBuffer(death_buffer);
}

Player & Player::operator=(const Player &other)
{
    if (this == &other)
        return *this;
    body = other.body;
    texture = other.texture;
    death_buffer = other.death_buffer;
    stats = other.stats;
    isDead = other.isDead;
    jumpHeight = other.jumpHeight;
    body.setTexture(&texture);
    death_sound.setBuffer(death_buffer);
    return *this;
}

sf::Vector2f Player::getPosition() const {
    return body.getPosition();
}


void Player::triggerDeath() {
    this->death_sound.play();
    isDead = true;
    deathEffect.trigger(this->body.getPosition(), 150, sf::Color(220, 220, 71));
}

bool Player::getState() const {
    return isDead;
}

void Player::handleDeath(double deltaTime, sf::RenderWindow &window) {
    if (isDead) {
        deathEffect.render(window);
        bool effectActive = deathEffect.update(deltaTime);
        if (!effectActive) {
            isDead = false;
        }
    }
}

void Player::updatePlayer(const double deltaTime) {
    //aceasta functie este folosita pentru a gestiona actiunea de saritura
    //a playerului la apasarea tastei space
    //intrucat playerul nu se misca ,ci tot ce este in jurul sau se misca de la dreapta
    //la stanga , ne vom ocupa doar de miscarea playerului pe axa Oy
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !stats.isJumping) {
        stats.isJumping = true;
        //7500-constanta a gravitatii ,mai mare pentru un gameplay mai apropiat de jocul
        //original
        stats.jumpSpeed = -sqrtf(2.0f * GRAVITY * jumpHeight);
    }
    //daca sare atunci se va aplica o gravitatie care este de 2 ori mai mica decat
    //saritura playerului
    if (stats.isJumping) {
        stats.jumpSpeed += GRAVITY * deltaTime;
        stats.rotationAngle += 350.0f * deltaTime;
        // rotationAngle=400.0f;
    }
    body.move(0.0f, static_cast<float>(stats.jumpSpeed * deltaTime));
    if (stats.rotationAngle >= 360.0f) stats.rotationAngle -= 360.0f;


    body.setRotation(static_cast<float>(stats.rotationAngle));
}
void Player::renderPlayer(sf::RenderWindow &window) {
    if (!isDead) {
        window.draw(body);
    }
}

void Player::handleCollisionGround(const Ground &ground) {
    if (checkCollisionGround(ground)) {
        // this->body.setPosition(this->body.getPosition().x,ground.getBounds1().top-this->getBounds().height/2.0f);
        stats.rotationAngle = calculateFallingSide(stats.rotationAngle);
        this->body.setPosition(this->body.getPosition().x, ground.getBounds1().top - 50.0f);
        stats.isJumping = false;
        stats.jumpSpeed = 0.0f;
    }
}

bool Player::checkCollisionGround(const Ground &ground) const {
    return (this->body.getGlobalBounds().intersects(ground.getBounds1())
            || this->body.getGlobalBounds().intersects(ground.getBounds2()));
}

//785, coord y pentru plasarea blocurilor pe podea
sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}
double Player::calculateFallingSide(double angle) {
    int side = static_cast<int>((angle + 45.0f) / 90) % 4;
    return side * 90;
}

//
// void Player::fellFromBlock(const bool &jumpState) {
//     if (jumpState == false) {
//         stats.rotationAngle = calculateFallingSide(stats.rotationAngle);
//     }
//     stats.isJumping = jumpState;
// }

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

void Player::moveTowardsEnd(float velocity, double deltaTime) {
    this->body.move(static_cast<float>(velocity * deltaTime), 0.0f);
}

void Player::applyChanges(const PlayerStatChanges &changes, bool &restartGame, float &velocity) {
    for (const auto &[key,value]: changes) {
        if (key == "rotationAngle") stats.rotationAngle = std::get<double>(value);
        else if (key == "isJumping") stats.isJumping = std::get<bool>(value);
        else if (key == "jumpSpeed") stats.jumpSpeed = std::get<float>(value);
        else if (key == "positionY") {
            stats.positionY = std::get<float>(value);
            this->body.setPosition(this->body.getPosition().x, stats.positionY);
        } else if (key == "restartGame") {
            restartGame = std::get<bool>(value);
            velocity = 0.0f;
        }
    }
}

double Player::getRotationAngle() {
    return stats.rotationAngle;
}
