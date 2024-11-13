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
    Obstacle(sf::Vector2f position, ObstacleType type);

    ~Obstacle()=default;
    Obstacle(const Obstacle& obstacle);
    Obstacle& operator=(const Obstacle& obstacle);
    friend std::ostream& operator<<(std::ostream& os, const Obstacle& obstacle);
    void updateObstacle(float velocity,double deltaTime);
    void renderObstacle(sf::RenderWindow &window);
    sf::Vector2f getPosition() const ;
    sf::FloatRect getBounds() const;

    void initializeObstacle(const std::string &texturePath, sf::Vector2f bodySize
    , sf::Vector2f hitboxSize, sf::Color fillColor, float outlineThickness);

    ObstacleType getType() const;
};

#endif
