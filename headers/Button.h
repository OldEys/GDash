#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {

    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

public:
    Button(const std::string &label, const sf::Vector2f &position, const sf::Vector2f &size);

    void render(sf::RenderWindow &window);

    bool isMouseOver(const sf::RenderWindow &window) const;

    void setColor(const sf::Color &color);

};

#endif //BUTTON_H
