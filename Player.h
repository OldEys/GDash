//
// Created by Babii Victor on 10/18/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

#include "Ground.h"
#include <SFML/Graphics.hpp>


class Player {
    sf::RectangleShape body;
    sf::Texture texture;
    bool isJumping;
    float jumpSpeed;
    float jumpHeight;

    public:
    Player();
    ~Player();

    Player(const Player &other)
        : body(other.body),
          texture(other.texture),
          isJumping(other.isJumping),
          jumpSpeed(other.jumpSpeed),
          jumpHeight(other.jumpHeight) {
        std::cout<<"copy constructor"<<std::endl;
    }

    Player & operator=(const Player &other) {
        if (this == &other)
            return *this;
        body = other.body;
        texture = other.texture;
        isJumping = other.isJumping;
        jumpSpeed = other.jumpSpeed;
        jumpHeight = other.jumpHeight;
        return *this;
    }

    void setPosition(float position);
    void updatePlayer(float deltaTime,const Ground &ground);
    void renderPlayer(sf::RenderWindow &window);
    void checkCollisionGround(const Ground &ground);


};



#endif //PLAYER_H
