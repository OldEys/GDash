
#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include <SFML/Graphics.hpp>


class GameFont {
    sf::Font font;
    sf::Text attempts_text;
    int attempts_number = 1;

public:
    GameFont();

    // explicit GameFont(sf::Vector2f pos);

    void update_attempts_number();

    // sf::Font getFont();
    void update_position(float velocity, double deltaTime);

    void render(sf::RenderWindow &window);

    void resetPosition(sf::Vector2f newPosition);

};
#endif //FONTMANAGER_H
