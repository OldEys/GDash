#include"../headers/DeathEffect.h"

#include <iostream>
#include<random>

DeathEffect::DeathEffect() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution distrib(radiusMin, radiusMax);
    particles.resize(100);
    for (auto &p: particles) {
        float radius = distrib(mt);
        p.particle.setRadius(radius);
        p.particle.setFillColor(color);
        p.particle.setOrigin(radius / 2.0f, radius / 2.0f);
    }
    centerParticle.setRadius(centerParticleRadius);
}

void DeathEffect::trigger(sf::Vector2f position, int numParticles, sf::Color color) {
    particles.resize(numParticles);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> degDistrib(0, 360.0f);
    std::uniform_real_distribution<double> spDistrib(speedMin, speedMax);

    // centerParticleRadius=10.0f;
    centerParticle.setOrigin(centerParticleRadius / 2.0f, centerParticleRadius / 2.0f);
    // centerParticle.setRadius(centerParticleRadius);
    centerParticle.setPosition(position);
    centerParticle.setFillColor(color);
    centerParticle.setScale(1.0f, 1.0f);

    for (auto &p: particles) {
        p.particle.setPosition(position);
        double angle = degDistrib(mt) * 3.1416 / 180.0f;
        double speed = spDistrib(mt);
        p.velocity = sf::Vector2f(static_cast<float>(speed * cos(angle)), static_cast<float>(speed * sin(angle)));
        p.particle.setFillColor(color);
    }
}

void DeathEffect::render(sf::RenderWindow &window) {
    std::cout << "randez particule\n";
    window.draw(centerParticle);
    for (const auto &p: particles) {
        window.draw(p.particle);
    }
}

bool DeathEffect::update(double deltaTime) {
    std::cout << "update particles\n";
    bool anyParticleActive = false;
    for (auto &p: particles) {
        p.velocity.x *= 0.95;
        p.velocity.y *= 0.95;
        p.particle.move(static_cast<float>(p.velocity.x * deltaTime), static_cast<float>(p.velocity.y * deltaTime));
        sf::Color color = p.particle.getFillColor();
        if (color.a > 5) {
            color.a -= 5;
            p.particle.setFillColor(color);
            anyParticleActive = true;
        }
    }
    float scaleFactor = 1.05f;
    centerParticle.setScale(centerParticle.getScale().x * scaleFactor, centerParticle.getScale().y * scaleFactor);
    // centerParticle.setOrigin(centerParticleRadius/2.0f,centerParticleRadius/2.0f);
    centerParticle.setOrigin(centerParticleRadius, centerParticleRadius);
    sf::Color color = centerParticle.getFillColor();
    if (color.a > 5) {
        color.a -= 5;
        centerParticle.setFillColor(color);
    }
    return anyParticleActive;
}

