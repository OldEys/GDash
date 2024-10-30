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

    void updatePlayer(double deltaTime,const Ground &ground);
    void renderPlayer(sf::RenderWindow &window);
    void checkCollisionGround(const Ground &ground);
    void checkCollisionObstacle(bool& endGame,double deltaTime,float& velocity,const Obstacle &obstacle);
    sf::FloatRect getBounds() const;
};

#endif //PLAYER_H