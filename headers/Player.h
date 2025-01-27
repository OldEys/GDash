#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <ostream>
#include <unordered_map>
#include <variant>

#include "Ground.h"
#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>
#include "DeathEffect.h"
struct PlayerStats {
    double rotationAngle;
    bool isJumping;
    float jumpSpeed;
    float positionY;
};

using PlayerStatChanges = std::unordered_map<std::string, std::variant<float, bool, int, double> >;

class Player {
    sf::RectangleShape body;
    sf::Texture texture;
    DeathEffect deathEffect;
    sf::SoundBuffer death_buffer;
    sf::Sound death_sound;
    PlayerStats stats;
    bool isDead;
    float jumpHeight;

    std::array<sf::Vector2f, 4> getOrientedBoundingBox();

    void projectOntoAxis(const std::array<sf::Vector2f, 4> &points, const sf::Vector2f &axis, float &min, float &max);

    bool checkCollisionGround(const Ground &ground) const;

public:
    explicit Player(float position);
    Player();
    ~Player();

    void setPosition(float x, float x1);

    Player(const Player &other);

    Player & operator=(const Player &other);
    sf::Vector2f getPosition() const ;

    friend std::ostream & operator<<(std::ostream &os, const Player &obj) {
        os << "is it jumping ?: " << obj.stats.isJumping << "\n";
        os<< "jumpHeight: " << obj.jumpHeight << "\n";
        os << "jumpSpeed: " << obj.stats.jumpSpeed << "\n";
        os << " position x: " << obj.getPosition().x << " position y: " << obj.getPosition().y << "\n";
        return os;
    }

    void triggerDeath();

    bool getState() const;

    void handleDeath(double deltaTime, sf::RenderWindow &window);

    void updatePlayer(double deltaTime);

    void renderPlayer(sf::RenderWindow &window);

    void handleCollisionGround(const Ground &ground);

    sf::FloatRect getBounds() const;

    double calculateFallingSide(double angle);

    void moveTowardsEnd(float velocity, double deltaTime);

    bool boundingBoxTest(const sf::Vector2f &obstaclePosition, const sf::Vector2f &obstacleSize,
                         float obstacleRotation);

    void applyChanges(const PlayerStatChanges &changes, bool &restartGame, float &velocity);

    double getRotationAngle();
};
#endif //PLAYER_H