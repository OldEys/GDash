#include "Ground.h"
#include <iostream>

Ground::Ground(const sf::RenderWindow &window) : groundTexture() {
    if (!groundTexture.loadFromFile("../images/ground-long.png")) {
        std::cerr << "Failed to load ground texture!" << std::endl;
    }
    
    groundBody1.setTexture(&groundTexture);
    float scaleX = static_cast<float>(window.getSize().x) / static_cast<float>(groundTexture.getSize().x);
    float scaleY = scaleX;
    groundBody1.setSize(sf::Vector2f(static_cast<float>(groundTexture.getSize().x), static_cast<float>(groundTexture.getSize().y)));
    groundBody1.setScale(scaleX, scaleY);
    groundBody1.setPosition(0.0f, static_cast<float>(window.getSize().y) - scaleY * groundBody1.getSize().y);


    groundBody2 = groundBody1;
    groundBody2.setPosition(groundBody1.getPosition().x + groundBody1.getGlobalBounds().width, groundBody1.getPosition().y);
}

Ground::Ground(const Ground &other) : groundTexture(other.groundTexture), groundBody1(other.groundBody1), groundBody2(other.groundBody2) {
    std::cout<<"Constructor de copiere"<<std::endl;
}


Ground & Ground::operator=(const Ground &other) {
    groundTexture=other.groundTexture;
    groundBody1=other.groundBody1;
    groundBody2=other.groundBody2;
    groundBody1.setTexture(&groundTexture);
    groundBody2.setTexture(&groundTexture);
    groundBody1.setFillColor(sf::Color(100, 100, 255));
    groundBody2.setFillColor(sf::Color(100, 100, 255));
    std::cout<<"Operator= de atribuire"<<std::endl;
    return *this;
}

Ground::~Ground() {
    std::cout <<"Destroyed ground\n";
}

void Ground::updateGround(float velocity, double deltaTime) {

    groundBody1.move(static_cast<float>(velocity * deltaTime), 0.0f);
    groundBody2.move(static_cast<float>(velocity * deltaTime), 0.0f);

    if (groundBody1.getPosition().x + groundBody1.getGlobalBounds().width < 0) {
        groundBody1.setPosition(groundBody2.getPosition().x + groundBody2.getGlobalBounds().width, groundBody1.getPosition().y);
    }
    if (groundBody2.getPosition().x + groundBody2.getGlobalBounds().width < 0) {
        groundBody2.setPosition(groundBody1.getPosition().x + groundBody1.getGlobalBounds().width, groundBody2.getPosition().y);
    }
}

void Ground::renderGround(sf::RenderWindow &window) {
    window.draw(groundBody1);
    window.draw(groundBody2);
}


float Ground::getGroundPos() {
    return groundBody1.getPosition().y;
}

sf::FloatRect Ground::getBounds1() const {
    return groundBody1.getGlobalBounds();
}

sf::FloatRect Ground::getBounds2() const {
    return groundBody2.getGlobalBounds();
}
