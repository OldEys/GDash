#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <ostream>

#include "Ground.h"
#include <SFML/Graphics.hpp>

#include "SFML/Audio.hpp"


class Player {
    sf::RectangleShape body;
    sf::Texture texture;
    bool isJumping;
    double jumpSpeed;
    float jumpHeight;
    double rotationAngle=0.0f;

public:
    explicit Player(float position);
    Player();
    ~Player();

    void setPosition(float x, float x1);

    Player(const Player &other);

    Player & operator=(const Player &other);
    sf::Vector2f getPosition() const ;

    friend std::ostream & operator<<(std::ostream &os, const Player &obj) {
        os << "is it jumping ?: " << obj.isJumping << "\n";
        os<< "jumpHeight: " << obj.jumpHeight << "\n";
        os<< "jumpSpeed: " << obj.jumpSpeed << "\n";
        os<<" position x: " << obj.getPosition().x<<"position y: " <<obj.getPosition().y << "\n";
        return os;
    }

    void updatePlayer(double deltaTime);

    void renderPlayer(sf::RenderWindow &window);

    void handleCollisionGround(const Ground &ground);

    bool checkCollisionGround(const Ground &ground) const;

    void handleLandingOnObstacle(float positionY);

    void handleLeftCollision(bool &endGame, float &velocity);

    sf::FloatRect getBounds() const;

    double calculateFallingSide(double angle);

    void fellFromBlock(const bool &jumpState);

    std::array<sf::Vector2f, 4> getOrientedBoundingBox();

    void projectOntoAxis(const std::array<sf::Vector2f, 4> &points, const sf::Vector2f &axis, float &min, float &max);

    bool boundingBoxTest(const sf::Vector2f &obstaclePosition, const sf::Vector2f &obstacleSize,
                         float obstacleRotation);
};
#endif //PLAYER_H