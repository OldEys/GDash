
#ifndef DEATHEFFECT_H
#define DEATHEFFECT_H
#include <SFML/Graphics.hpp>

class DeathEffect {
    struct Particle {
        sf::CircleShape particle;
        sf::Vector2f velocity;
    };

    std::vector<Particle> particles;
    int particleCount = 0;
    sf::Color color;
    float radiusMin = 5.0f, radiusMax = 10.0f;
    float speedMin = 0.0f, speedMax = 300.0f;
    sf::CircleShape centerParticle;
    float centerParticleRadius = 10.0f;

public:
    DeathEffect();

    void render(sf::RenderWindow &window);

    bool update(double deltaTime);

    void trigger(sf::Vector2f position, int numParticles, sf::Color color);
};
#endif
