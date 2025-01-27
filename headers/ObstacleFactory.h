#ifndef OBSTACLEFACTORY_H
#define OBSTACLEFACTORY_H
#include <map>
#include <functional>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Block.h"
#include "Spike.h"
#include "Platform.h"
#include "Short_Spike.h"
#include "JumpOrb.h"
#include "Final.h"


class ObstacleFactory {
public:
    ObstacleFactory();

    std::shared_ptr<Obstacle> createObstacle(const std::string &type, const sf::Vector2f &position) const;

private:
    std::map<std::string, std::function<std::shared_ptr<Obstacle>(sf::Vector2f)> > factoryMap;
};

#endif //OBSTACLEFACTORY_H
