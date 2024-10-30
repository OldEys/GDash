
#ifndef CHUNK_H
#define CHUNK_H
#include <vector>

#include "Obstacle.h"


class Chunk {
    std::vector<Obstacle> obstacles;
    float startX;
    float endX;
    public:
    Chunk(float startX, float chunkSize);
    ~Chunk();
    friend std::ostream& operator<<(std::ostream& os, const Chunk& chunk);
    void addObstacle(const Obstacle& obstacle);
    [[nodiscard]] float getStartX() const ;
    [[nodiscard]] const std::vector<Obstacle>& getObstacles()const;
    [[nodiscard]] float getEndX() const;

};



#endif //CHUNK_H
