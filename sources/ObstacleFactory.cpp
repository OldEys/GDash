#include"../headers/ObstacleFactory.h"

#include <iostream>

ObstacleFactory::ObstacleFactory()
    : factoryMap{
            {"block", [](sf::Vector2f pos) { return Block(pos).clone(); }},
            {"spike", [](sf::Vector2f pos) { return Spike(pos).clone(); }},
            {"platform", [](sf::Vector2f pos) { return Platform(pos).clone(); }},
            {"short", [](sf::Vector2f pos) { return Short_Spike(pos).clone(); }},
            {"jumporb", [](sf::Vector2f pos) { return JumpOrb(pos).clone(); }},
            {"final", [](sf::Vector2f pos) { return Final(pos).clone(); }}
    } {}

std::shared_ptr<Obstacle> ObstacleFactory::createObstacle(const std::string &type, const sf::Vector2f &position) const {
    auto obs = factoryMap.find(type);
    if (obs != factoryMap.end()) {
        return obs->second(position);
    }
    std::cerr << "Cant recognize object type: " << type << "\n";
    return nullptr;
}
