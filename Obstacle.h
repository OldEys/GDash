//
// Created by Babii Victor on 10/20/2024.
//

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/Graphics.hpp>

enum class ObstacleType {
    SPIKE,
    BLOCK,
    SPIKE_SHORT,
    PLATFORM,
    END
};
class Obstacle {
    sf::RectangleShape body;
    sf::RectangleShape hitbox;
    sf::Texture texture;
    sf::Vector2f position;
    ObstacleType type;

public:
    Obstacle(ObstacleType type,sf::Vector2f position);
    ~Obstacle()=default;
    Obstacle();
    Obstacle(const Obstacle& obstacle);
    Obstacle& operator=(const Obstacle& obstacle);
    friend std::ostream& operator<<(std::ostream& os, const Obstacle& obstacle);
    void updateObstacle(float velocity,double deltaTime);
    void renderObstacle(sf::RenderWindow &window);
    sf::Vector2f getPosition() const ;
    sf::FloatRect getBounds() const;
    ObstacleType getType() const;
};

#endif
