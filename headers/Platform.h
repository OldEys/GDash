#ifndef PLATFORM_H
#define PLATFORM_H
#include<memory>
#include"Obstacle.h"
class Platform : public Obstacle{

public:
    Platform()=default;
    explicit Platform(const sf::Vector2f& pos,const std::string& texturePath);
    std::shared_ptr<Obstacle> clone()const override {
        return std::make_shared<Platform>(*this);
    }
private:
    void onCollision(Player& player,bool &endGame,float& velocity) const override;

    bool isOnTopOfBlock(const Player &player) const;

    bool fallingFromBlock(const Player &player) const;
};

#endif //PLATFORM_H
