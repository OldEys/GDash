// //
// // Created by Babii Victor on 10/20/2024.
// //
//
// #include "Obstacle.h"
//
// Obstacle::Obstacle(ObstacleType type,float xPos) {
//     this->body.setPosition(xPos,750.0f);
//     if(this->type== ObstacleType::BLOCK) {
//         this->texture.loadFromFile("../images/ground-block.png");
//         body.setSize(sf::Vector2f(120.0f,120.0f));
//         body.setTexture(&this->texture);
//     }
//     if(this->type== ObstacleType::SPIKE) {
//         this->texture.loadFromFile("../images/ground.png");
//         body.setSize(sf::Vector2f(60.0f,60.0f));
//         body.setTexture(&this->texture);
//     }
//     this->body.setFillColor(sf::Color::Black);
//     this->body.setOutlineColor(sf::Color::White);
//     this->body.setOutlineThickness(4.0f);
// }
//
// void Obstacle::updateObstacle(float velocity,float deltaTime) {
//     body.move(velocity*deltaTime,0.0f);
// }
//
// void Obstacle::renderObstacle(sf::RenderWindow &window) {
//     window.draw(this->body);
// }
//
