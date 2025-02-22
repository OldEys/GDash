

#ifndef JUMPORB_H
#define JUMPORB_H
#include "Obstacle.h"

class JumpOrb : public Obstacle {
public:
    explicit JumpOrb(const sf::Vector2f &pos);

    std::shared_ptr<Obstacle> clone() const override {
        return std::make_shared<JumpOrb>(*this);
    }

private:
    void afis(std::ostream &os) const override;

    PlayerStatChanges onCollisionImplem(Player &player) override;
};

#endif //JUMPORB_H
