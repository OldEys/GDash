#ifndef ATTEMPTCOUNTER_H
#define ATTEMPTCOUNTER_H
#include <SFML/Graphics.hpp>

class AttemptCounter {
    sf::Font font;
    sf::Text attempts_text;
    int attempts_number = 1;

public:
    AttemptCounter();

    void update_attempts_number();

    void update_position(float velocity, double deltaTime);

    void render(sf::RenderWindow &window);

    void resetPosition(sf::Vector2f newPosition);

};
#endif //ATTEMPTCOUNTER_H
