
#ifndef FINAL_H
#define FINAL_H
#include"Obstacle.h"

class Final : public Obstacle {
    bool endGame;

public:

    explicit Final(const sf::Vector2f &pos);

    std::shared_ptr<Obstacle> clone() const override {
        return std::make_shared<Final>(*this);
    }
    void finalProximity(Player &player, float &velocity, double deltaTime);

    void closeGame(sf::RenderWindow &window);

private:
    PlayerStatChanges onCollisionImplem(Player &player) override;

    void afis(std::ostream &os) const override;
};
#endif //FINAL_H
