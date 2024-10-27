
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
    void addObstacle(Obstacle obstacle);
    float getStartX();
    const std::vector<Obstacle>& getObstacles()const;
    float getEndX();

};



#endif //CHUNK_H
