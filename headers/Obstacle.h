#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <memory>
#include "Player.h"
#include "TextureManager.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics.hpp"

class Obstacle {
protected:
    sf::RectangleShape body;
    sf::RectangleShape hitbox;
    sf::Texture texture;
    sf::Vector2f position;
    static TextureManager texture_manager;
public:
    void adjustPositionX(float offset);
    sf::Vector2f getPosition()const;
    Obstacle()=default;
    virtual ~Obstacle()=default;
    Obstacle(const Obstacle&);
    Obstacle& operator=(const Obstacle&);
    Obstacle(Obstacle&&) noexcept;
    Obstacle& operator=(Obstacle&&) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Obstacle& obstacle);

    void updateObstacle(float velocity,double deltaTime);
    void renderObstacle(sf::RenderWindow& window);
    void nviOnCollision(Player& player,bool &endGame,float& velocity){
        onCollision(player,endGame,velocity);
    }
    virtual std::shared_ptr<Obstacle> clone()const=0;
private:
    virtual void onCollision(Player& player,bool &endGame,float& velocity)const=0;
};

#endif
