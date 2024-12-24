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

void DeathEffect::trigger(sf::Vector2f position, int numParticles, sf::Color particleColor) {
    particles.resize(numParticles);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> degDistrib(0, 360.0f);
    std::uniform_real_distribution<double> spDistrib(speedMin, speedMax);

    centerParticle.setOrigin(centerParticleRadius / 2.0f, centerParticleRadius / 2.0f);
    // centerParticle.setRadius(centerParticleRadius);
    centerParticle.setPosition(position);
    centerParticle.setFillColor(particleColor);
    centerParticle.setScale(1.0f, 1.0f);

    for (auto &p: particles) {
        p.particle.setPosition(position);
        double angle = degDistrib(mt) * 3.1416 / 180.0f;
        double speed = spDistrib(mt);
        p.velocity = sf::Vector2f(static_cast<float>(speed * cos(angle)), static_cast<float>(speed * sin(angle)));
        p.particle.setFillColor(particleColor);
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
        p.velocity.x *= 0.95f;
        p.velocity.y *= 0.95f;
        p.particle.move(static_cast<float>(p.velocity.x * deltaTime), static_cast<float>(p.velocity.y * deltaTime));
        sf::Color c = p.particle.getFillColor();
        if (c.a > 5) {
            c.a -= 5;
            p.particle.setFillColor(c);
            anyParticleActive = true;
        }
    }
    float scaleFactor = 1.05f;
    centerParticle.setScale(centerParticle.getScale().x * scaleFactor, centerParticle.getScale().y * scaleFactor);
    // centerParticle.setOrigin(centerParticleRadius/2.0f,centerParticleRadius/2.0f);
    centerParticle.setOrigin(centerParticleRadius, centerParticleRadius);
    sf::Color c_cent = centerParticle.getFillColor();
    if (c_cent.a > 5) {
        c_cent.a -= 5;
        centerParticle.setFillColor(c_cent);
    }
    return anyParticleActive;
}

