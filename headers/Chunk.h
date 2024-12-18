#ifndef CHUNK_H
#define CHUNK_H
#include <vector>

#include "Obstacle.h"


class Chunk {
    // static int id_max;
    // int id;
    std::vector<std::shared_ptr<Obstacle>>obstacles;
    float startX;
    float endX;
public:
    Chunk(float startX, float chunkSize);
    ~Chunk()=default;
    Chunk(const Chunk& other);
    Chunk& operator=(Chunk other);
    friend std::ostream& operator<<(std::ostream& os, const Chunk& chunk);

    void addObstacle(std::shared_ptr<Obstacle> obstacle);

    [[nodiscard]] float getStartX() const ;
    [[nodiscard]] const std::vector<std::shared_ptr<Obstacle>>& getObstacles()const;
    [[nodiscard]] float getEndX() const;
    friend void swap(Chunk& a, Chunk& b) noexcept ;

};

#endif //CHUNK_H
