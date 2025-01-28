#include"../headers/Platform.h"

#include <iostream>
#define ON_GROUND 785.0f

Platform::Platform(const sf::Vector2f& pos) : Obstacle("images/ground_block.png",sf::Vector2f(100.0f,40.0f),
    sf::Color(0,0,50),sf::Color::White,5.0f,sf::Vector2f(100.0f,40.0f)) {
    this->body.setPosition(pos);
    this->hitbox.setPosition(this->body.getPosition().x
                         + this->body.getGlobalBounds().width / 2.0f,
                         this->body.getPosition().y + this->body.getGlobalBounds().height / 2.0f);
}

PlayerStatChanges Platform::onCollisionImplem(Player &player) {
    PlayerStatChanges changes;
    if (this->hitbox.getGlobalBounds().intersects(player.getBounds())) {
        if (isOnTopOfBlock(player)) {
            if (player.getBounds().left + player.getBounds().width/1.15 > this->hitbox.getGlobalBounds().left ) {
                //pentru evitarea cazului in care playerul atinge coltul de sus si incepe sa pluteasca
                if (player.getPosition().y < this->hitbox.getGlobalBounds().top) {
                    changes["isJumping"] = false;
                    changes["positionY"] = this->hitbox.getGlobalBounds().top - player.getBounds().height/2.0f;
                    changes["rotationAngle"] = player.calculateFallingSide(player.getRotationAngle());
                    return changes;
                }
                if (player.getPosition().x < this->hitbox.getGlobalBounds().left ||
                    player.getPosition().y > this->hitbox.getGlobalBounds().top + this->hitbox.getGlobalBounds().
                    height) {
                    player.triggerDeath();
                    changes["restartGame"] = true;
                    return changes;
                }
            } else {
                if (player.getBounds().top + player.getBounds().height > this->hitbox.getGlobalBounds().top) {
                    player.triggerDeath();
                    changes["restartGame"] = true;
                    return changes;
                }
            }
        }
    } else {
        if (fallingFromBlock(player)) {
            changes["isJumping"] = true;
            if (player.getPosition().y >= ON_GROUND) {
                changes["isJumping"] = false;
                changes["rotationAngle"] = player.calculateFallingSide(player.getRotationAngle());
            }
        }
    }

    return changes;
}

bool Platform::isOnTopOfBlock(const Player &player) const {
    return (player.getBounds().top<this->hitbox.getGlobalBounds().top+
        this->hitbox.getGlobalBounds().height&&player.getBounds().top+player.getBounds().height>
    this->hitbox.getGlobalBounds().top);
}
bool Platform::fallingFromBlock(const Player& player)const {
    return ( player.getBounds().left > this->hitbox.getGlobalBounds().left +
            this->hitbox.getGlobalBounds().width && player.getBounds().top + player.getBounds().height
            > this->hitbox.getGlobalBounds().top);
}

void Platform::afis(std::ostream &os) const {
    os<<"This is a platform\n";
}
