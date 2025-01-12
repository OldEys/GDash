
#ifndef SHORT_SPIKE_H
#define SHORT_SPIKE_H
#include <memory>
#include "Obstacle.h"

class Short_Spike : public Obstacle{

public:
    Short_Spike()=default;
    explicit Short_Spike(const sf::Vector2f& pos);
    std::shared_ptr<Obstacle> clone()const override {
        return std::make_shared<Short_Spike>(*this);
    }
private:
    void onCollision(Player &player, bool &restartGame, float &velocity) override;

    void afis(std::ostream &os) const override;
};

#endif //SHORT_SPIKE_H
