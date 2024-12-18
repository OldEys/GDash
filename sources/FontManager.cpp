#include"../headers/FontManager.h"

#include <iostream>

GameFont::GameFont() {
    if (!font.loadFromFile("font/game_font.otf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    attempts_text.setFont(font);
    attempts_text.setCharacterSize(100);
    attempts_text.setOutlineColor(sf::Color::Black);
    attempts_text.setOutlineThickness(4.5f);
    attempts_text.setString("Attempt " + std::to_string(attempts_number));
    attempts_text.setPosition(sf::Vector2f(500, 300));
}

void GameFont::update_attempts_number() {
    this->attempts_number++;
    attempts_text.setString("Attempt " + std::to_string(attempts_number));
}

void GameFont::update_position(float velocity, double deltaTime) {
    if (attempts_text.getPosition().x > -600.0f) {
        attempts_text.move(static_cast<float>(velocity * deltaTime), 0);
    }
}

void GameFont::render(sf::RenderWindow &window) {
    window.draw(attempts_text);
}

void GameFont::resetPosition(sf::Vector2f newPosition) {
    this->attempts_text.setPosition(newPosition);
}

sf::Text GameFont::getAttempts_text() {
    return attempts_text;
}
