//
// Created by Babii Victor on 10/25/2024.
//

#include "Chunk.h"

#include <iostream>
int Chunk::id_max = 0;

Chunk::Chunk(float startX, float chunkSize) : id(id_max), startX(startX), endX(startX + chunkSize)  {
    std::cout<<"Created chunk"<<id<<"\n";
    ++id_max;
}

// Chunk::~Chunk() {
//     std::cout<<"Destroyed chunk"<<id<<"\n";
// }

void Chunk::addObstacle(Obstacle& obstacle) {
    // obstacles.push_back(obstacle);
    obstacles.emplace_back(std::move(obstacle));
}

[[nodiscard]] float Chunk::getStartX() const {
    return this->startX;
}

[[nodiscard]] const std::vector<Obstacle> & Chunk::getObstacles() const {
    return this->obstacles;
}

[[nodiscard]] float Chunk::getEndX() const {
    return this->endX;
}
std::ostream & operator<<(std::ostream &os, const Chunk &chunk) {
    os<<"Start X: "<<chunk.getStartX()<<"\n";
    os<<"End X: "<<chunk.getEndX()<<"\n";
    os<<"Obstacles:\n";
    for(const auto& obstacle : chunk.obstacles) {
        os<<obstacle<<"\n";
    }
    return os;
}
