//
// Created by Babii Victor on 10/18/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

#include "Ground.h"
#include <SFML/Graphics.hpp>

#include "Obstacle.h"


class Player {
    sf::RectangleShape body;
    sf::Texture texture;
    bool isJumping;
    float jumpSpeed;
    float jumpHeight;

    public:
    explicit Player(float position);
    Player()=default;
    ~Player();

    Player(const Player &other);

    Player & operator=(const Player &other);

    sf::Vector2f getPosition() const ;
    void updatePlayer(double deltaTime,const Ground &ground);
    void renderPlayer(sf::RenderWindow &window);
    void checkCollisionGround(const Ground &ground);
    void checkCollisionObstacle(float deltaTime,float& velocity,const Obstacle &obstacle);
    sf::FloatRect getBounds() const;
};

#endif //PLAYER_H