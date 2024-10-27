//
// Created by Babii Victor on 10/25/2024.
//

#include "Chunk.h"

#include <iostream>

Chunk::Chunk(float startX, float chunkSize) : startX(startX), endX(startX + chunkSize)  {
    std::cout<<"Created chunk\n";
}

Chunk::~Chunk() {
    std::cout<<"Destroyed chunk\n";
}

void Chunk::addObstacle(Obstacle obstacle) {
    obstacles.push_back(obstacle);
}

float Chunk::getStartX() {
    return this->startX;
}

const std::vector<Obstacle> & Chunk::getObstacles() const {
    return this->obstacles;
}

float Chunk::getEndX() {
    return this->endX;
}
