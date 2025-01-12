#ifndef GROUND_H
#define GROUND_H

#include <ostream>
#include <SFML/Graphics.hpp>
class Ground {
    sf::Texture groundTexture;
    sf::RectangleShape groundBody1;
    sf::RectangleShape groundBody2;

public:
    explicit Ground(const sf::RenderWindow &window);
    friend std::ostream & operator<<(std::ostream &os, const Ground &obj) {
               os<< " groundBody1 position x : " << obj.groundBody1.getPosition().x<<" y: "<<obj.groundBody1.getPosition().y;
               os<< " groundBody2 position x : " << obj.groundBody2.getPosition().x<<" y: "<<obj.groundBody2.getPosition().y;
        return os;
    }

    Ground()=default;
    Ground(const Ground &other) ;
    Ground& operator=(const Ground &other);
    ~Ground();
    void updateGround(float velocity, double deltaTime);
    void renderGround(sf::RenderWindow &window);
    float getGroundPos();
    sf::FloatRect getBounds1() const;
    sf::FloatRect getBounds2() const;
};

#endif // GROUND_H
