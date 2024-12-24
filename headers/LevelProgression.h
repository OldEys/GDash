#ifndef LEVELPROGRESSION_H
#define LEVELPROGRESSION_H
#include <SFML/Graphics.hpp>

class LevelProgression {
    sf::Font font;
    sf::Text level_percent;
    sf::ConvexShape progress_bar;
    sf::RectangleShape progress_bar_fill;
    const float border_radius=12.5f;
    const float border_width=750.0f;
    const float border_height=25.0f;
    double percent=0;
public:
    LevelProgression();
    void updatePercent(double totalDistanceTravelled,double levelLength);
    void render(sf::RenderWindow &window);
    // void updatePosition(sf::RenderWindow &window);
    sf::ConvexShape RoundedRectangle(float pos_x, float pos_y, float rectWidth, float rectHeight,float radius,
        const sf::Color &col,float Outline,const sf::Color& OutlineCol);


};
#endif //LEVELPROGRESSION_H
