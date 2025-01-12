#ifndef BLOCK_H
#define BLOCK_H
#include <memory>

#include "Obstacle.h"

class Block : public Obstacle{

public:
    Block()=default;
    explicit Block(const sf::Vector2f& pos);
    std::shared_ptr<Obstacle> clone()const override {
        return std::make_shared<Block>(*this);
    }
private:
    void onCollision(Player &player, bool &restartGame, float &velocity) override;

    bool isOnTopOfBlock(const Player& player)const;
    bool fallingFromBlock(const Player& player)const;

    void afis(std::ostream &os) const override;
};
#endif //BLOCK_H
