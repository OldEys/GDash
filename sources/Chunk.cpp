#include "../headers/Chunk.h"

#include <iostream>
// int Chunk::id_max = 0;

Chunk::Chunk(float startX, float chunkSize) : /*id(id_max),*/ startX(startX), endX(startX + chunkSize)  {
}

Chunk::Chunk(const Chunk &other) : startX(other.startX), endX(other.endX) {
    for(const auto &obstacle : other.obstacles) {
        obstacles.emplace_back(obstacle->clone());
    }
}

Chunk & Chunk::operator=(Chunk other) {
    swap(*this,other);
    return *this;
}
// Chunk & Chunk::operator=(Chunk&& other) noexcept {
//     Chunk temp(std::move(other));
//     swap(*this,temp);
//     return *this;
// }
void Chunk::addObstacle(std::shared_ptr<Obstacle> obstacle) {
    obstacles.emplace_back(std::move(obstacle));
}
[[nodiscard]] float Chunk::getStartX() const {
    return this->startX;
}

[[nodiscard]] const std::vector<std::shared_ptr<Obstacle>> & Chunk::getObstacles() const {
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
        os<<*obstacle<<"\n";
    }
    os<<"\n";
    return os;
}

void swap(Chunk &a, Chunk &b) noexcept{
    std::swap(a.startX, b.startX);
    std::swap(a.endX, b.endX);
    std::swap(a.obstacles, b.obstacles);
}
