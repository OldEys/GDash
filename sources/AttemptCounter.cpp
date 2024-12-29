#include"../headers/AttemptCounter.h"
#include <iostream>

#include "../headers/Exceptions.h"

AttemptCounter::AttemptCounter() {
    if (!font.loadFromFile("font/game_font.otf")) {
        throw Font_error("font/game_font.otf");
    }
    attempts_text.setFont(font);
    attempts_text.setCharacterSize(100);
    attempts_text.setOutlineColor(sf::Color::Black);
    attempts_text.setOutlineThickness(4.5f);
    attempts_text.setString("Attempt " + std::to_string(attempts_number));
    attempts_text.setPosition(sf::Vector2f(500, 300));
}
void AttemptCounter::update_attempts_number() {
    this->attempts_number++;
    attempts_text.setString("Attempt " + std::to_string(attempts_number));
}

void AttemptCounter::update_position(float velocity, double deltaTime) {
    if (attempts_text.getPosition().x > -600.0f) {
        attempts_text.move(static_cast<float>(velocity * deltaTime), 0);
    }
}

void AttemptCounter::render(sf::RenderWindow &window) {
    window.draw(attempts_text);
}

void AttemptCounter::resetPosition(sf::Vector2f newPosition) {
    this->attempts_text.setPosition(newPosition);
}