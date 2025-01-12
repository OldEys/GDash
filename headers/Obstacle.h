#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <memory>
#include "Player.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class Obstacle {
protected:
    sf::RectangleShape body;
    sf::RectangleShape hitbox;
    sf::Texture texture;
    static TextureManager texture_manager;
public:
    Obstacle()=default;
    Obstacle(const std::string &texturePath, sf::Vector2f bodySize, sf::Color obsColor, sf::Color outColor,
             float outThick,
             sf::Vector2f hitboxSize);
    void adjustPositionX(float offset);
    sf::Vector2f getPosition()const;
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
    virtual void onCollision(Player &player, bool &endGame, float &velocity) =0;

    virtual void afis(std::ostream &os) const {
        os << "This is an unknown obstacle \n";
    };
};

#endif
