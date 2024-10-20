//
// Created by Babii Victor on 10/20/2024.
//

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "SFML/Graphics.hpp"


class Obstacle {
    // sf::RectangleShape body;
    sf::ConvexShape body;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    int type;

public:
    Obstacle(sf::Vector2f position, int type);
    ~Obstacle();
    void initTexture();
};

#endif //OBSTACLE_H
