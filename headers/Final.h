
#ifndef FINAL_H
#define FINAL_H
#include"Obstacle.h"

class Final : public Obstacle {
public:
    Final() = default;

    explicit Final(const sf::Vector2f &pos, const std::string &texturePath);

    std::shared_ptr<Obstacle> clone() const override {
        return std::make_shared<Final>(*this);
    }
    void finalProximity(Player &player, float &velocity, double deltaTime);
private:
    void onCollision(Player &player, bool &endGame, float &velocity) const override;
};
#endif //FINAL_H
