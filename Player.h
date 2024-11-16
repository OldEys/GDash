#ifndef PLAYER_H
#define PLAYER_H

#include <ostream>

#include "Ground.h"
#include <SFML/Graphics.hpp>

#include "Obstacle.h"


class Player {
    sf::RectangleShape body;
    sf::Texture texture;
    bool isJumping;
    double jumpSpeed;
    float jumpHeight;
    public:
    explicit Player(float position);
    Player();
    ~Player();

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

    void handleCollisionObstacle(bool &endGame, double deltaTime, float &velocity, const Obstacle &obstacle);

    bool checkCollisionObstacle(const Obstacle &obstacle) const;

    bool isAboveObstacle(double deltaTime, const Obstacle &obstacle) const;

    bool isCollidingFromSides(const Obstacle &obstacle) const;

    bool isOnTopOfObstacle(const Obstacle &obstacle) const;

    void handleLandingOnObstacle(const Obstacle &obstacle);

    void handleLeftCollision(bool &endGame, const Obstacle &obstacle, float &velocity);

    void handleSpikeCollision(bool &endGame, float &velocity);

    bool fallingFromBlock(const Obstacle &obstacle) const;

    sf::FloatRect getBounds() const;
};

#endif //PLAYER_H