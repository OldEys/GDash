
#ifndef SPIKE_H
#define SPIKE_H
#include <memory>
#include "Obstacle.h"

class Spike : public Obstacle{

public:
    Spike()=default;
    explicit Spike(const sf::Vector2f& pos);
    std::shared_ptr<Obstacle> clone()const override {
        return std::make_shared<Spike>(*this);
    }
private:
    void afis(std::ostream &os) const override;
    PlayerStatChanges onCollisionImplem(Player& player) override;
};

#endif //SPIKE_H
