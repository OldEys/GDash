#include "../headers/Button.h"

Button::Button(const std::string &label, const sf::Vector2f &position, const sf::Vector2f &size) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color::Blue);

    if (!font.loadFromFile("font/game_font.otf")) {
        throw std::runtime_error("font/game_font.otf");
    }

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void Button::render(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isMouseOver(const sf::RenderWindow &window) const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
}

void Button::setColor(const sf::Color &color) {
    shape.setFillColor(color);
}

