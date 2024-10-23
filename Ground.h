#ifndef GROUND_H
#define GROUND_H

#include "SFML/Graphics.hpp"
#include <iostream>

class Ground {
    sf::Texture groundTexture;
    sf::RectangleShape groundBody1;
    sf::RectangleShape groundBody2;

public:
    explicit Ground(sf::RenderWindow &window);
    Ground()=default;
    Ground(const Ground &other) ;
    Ground& operator=(const Ground &other);
    void updateGround(float velocity, float deltaTime);
    void renderGround(sf::RenderWindow &window);
    void initGround();
    float getGroundPos();
    const sf::FloatRect getBounds1() const;
    const sf::FloatRect getBounds2() const;
};

#endif // GROUND_H
