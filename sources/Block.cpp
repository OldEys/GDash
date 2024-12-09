#include "../headers/Block.h"


// void Block::onCollision(Player &player, bool &endGame, float &velocity) const override {
//     if(this->getBounds().intersects(player.getBounds())) {
//         if()
//
//     }
// }
// void Player::handleCollisionObstacle(bool &endGame, double deltaTime, float &velocity, const Obstacle &obstacle) {
//     if (checkCollisionObstacle(obstacle)) {
//         if (obstacle.getType() == ObstacleType::BLOCK || obstacle.getType() == ObstacleType::PLATFORM) {
//             if (isAboveObstacle(deltaTime, obstacle)) {
//                 //daca intersecteaza obstac    olul pe deasupra pozitionam playerul pe obstacol
//                 this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height/2.0f);
//                 isJumping = false;
//                 // body.setRotation(0.0f);
//                 rotationAngle=calculateFallingSide(rotationAngle);
//             }
//             else {
//                 //daca jucatorul intersecteaza obiectul prin stanga
//                 if (isCollidingFromSides(obstacle)) {
//                     //daca jucatorul intersecteaza obiectul de sus
//                     if (isOnTopOfObstacle(obstacle)) {
//                         if (this->body.getPosition().y < obstacle.getBounds().top) {
//                             //daca se afla pe obiect
//                             handleLandingOnObstacle(obstacle);
//                         } else {
//                             //se afla in stanga lui
//                             handleLeftCollision(endGame, obstacle, velocity);
//                         }
//                     }
//                 }
//             }
//         }
//         if (obstacle.getType() == ObstacleType::SPIKE || obstacle.getType() == ObstacleType::SPIKE_SHORT) {
//             handleSpikeCollision(endGame, velocity);
//         }
//         if(obstacle.getType()==ObstacleType::END) {
//             endGame = true;
//             std::cout<<"Level completed ! Well done!\n";
//         }
//     }
//     //else trateaza cazul in care player a cazut de pe bloc
//     //daca nu exista acest else player putea sa sara in timp ce cadea ,dupa ce fusese pe un bloc
//     else {
//         if (fallingFromBlock(obstacle)) {
//             isJumping = true;
//             if (this->body.getPosition().y >= ON_GROUND) {
//                 //daca dupa caderea de pe bloc a ajuns eventual pe sol resetam jump
//                 isJumping = false;
//             }
//         }
//     }
// }
//
// bool Player::fallingFromBlock(const Obstacle &obstacle) const {
//     return ((obstacle.getType() == ObstacleType::BLOCK || obstacle.getType() == ObstacleType::PLATFORM)
//             && this->body.getGlobalBounds().left > obstacle.getBounds().left +
//             obstacle.getBounds().width && this->body.getGlobalBounds().top + this->body.getGlobalBounds().height
//             > obstacle.getBounds().top);
// }
// bool Player::checkCollisionObstacle(const Obstacle &obstacle) const {
//     return (this->body.getGlobalBounds().intersects(obstacle.getBounds()));
// }
//
// bool Player::isAboveObstacle(double deltaTime, const Obstacle &obstacle) const {
//     return (this->getBounds().top + this->getBounds().height - jumpSpeed * deltaTime <= obstacle.getBounds().top);
// //verifica daca playerul urmeaza sa intersecteze un obiect pe deasupra
// }
//
// bool Player::isCollidingFromSides(const Obstacle &obstacle) const {
//     return (this->getBounds().left < obstacle.getBounds().left + obstacle.getBounds().width &&
//             this->getBounds().left + this->getBounds().width > obstacle.getBounds().left);
//     //verifica daca intersecteaza un obiect prin laterala
// }
//
// bool Player::isOnTopOfObstacle(const Obstacle &obstacle) const {
//     return (this->getBounds().top < obstacle.getBounds().top + obstacle.getBounds().height &&
//             this->getBounds().top + this->getBounds().height > obstacle.getBounds().top);
//     //verifica daca intersecteaza un obiect pe verticala
// }
//
// void Player::handleLandingOnObstacle(const Obstacle &obstacle) {
//     this->body.setPosition(this->body.getPosition().x, obstacle.getBounds().top - this->getBounds().height/2.0f);
//     isJumping = false;
// }
//
// void Player::handleLeftCollision(bool &endGame, const Obstacle &obstacle, float &velocity) {
//     this->body.setPosition(obstacle.getBounds().left - this->getBounds().width, this->body.getPosition().y/2.0f);
//     endGame = true;
//     velocity = 0.0f;
// }
//
// void Player::handleSpikeCollision(bool &endGame, float &velocity) {
//     endGame = true;
//     velocity = 0.0f;
//     jumpSpeed = 0.0f;
//     isJumping = false;
// }
