#ifndef PLATFORM_H
#define PLATFORM_H
#include<memory>
#include"Obstacle.h"
class Platform : public Obstacle{

public:
    Platform()=default;
    explicit Platform(const sf::Vector2f& pos);
    std::shared_ptr<Obstacle> clone()const override {
        return std::make_shared<Platform>(*this);
    }
private:
    void onCollision(Player& player,bool &restartGame,float& velocity) override;

    bool isOnTopOfBlock(const Player &player) const;

    bool fallingFromBlock(const Player &player) const;

    void afis(std::ostream& os)const override;
};

#endif //PLATFORM_H
