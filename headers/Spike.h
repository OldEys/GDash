
#ifndef SPIKE_H
#define SPIKE_H
#include <memory>
#include "Obstacle.h"

class Spike : public Obstacle{

public:
    Spike()=default;
    explicit Spike(const sf::Vector2f& pos,const std::string& texturePath);
    std::shared_ptr<Obstacle> clone()const override {
        return std::make_shared<Spike>(*this);
    }
private:
    void onCollision(Player& player,bool &endGame,float& velocity) const override;
};

#endif //SPIKE_H
