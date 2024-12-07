
#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <memory>
#include <SFML/Graphics.hpp>

#include "TextureManager.h"

enum class ObstacleType {
    SPIKE,
    BLOCK,
    SPIKE_SHORT,
    PLATFORM,
    END
};
class Obstacle {
    ObstacleType type;
    sf::RectangleShape body;
    sf::RectangleShape hitbox;
    sf::Texture texture;
    static TextureManager texture_manager;
    sf::Vector2f position;

public:
    Obstacle(sf::Vector2f position, ObstacleType type);

    ~Obstacle()=default;

    Obstacle(Obstacle&& other)noexcept;
    Obstacle& operator=(Obstacle&& other)noexcept;
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
