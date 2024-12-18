#ifndef BLOCK_H
#define BLOCK_H
#include <memory>

#include "Obstacle.h"

class Block : public Obstacle{

public:
    Block()=default;
    explicit Block(const sf::Vector2f& pos,const std::string& texturePath);
    std::shared_ptr<Obstacle> clone()const override {
        return std::make_shared<Block>(*this);
    }
private:
    void onCollision(Player& player,bool &endGame,float& velocity) const override;
    bool isOnTopOfBlock(const Player& player)const;
    bool fallingFromBlock(const Player& player)const;
};
#endif //BLOCK_H
