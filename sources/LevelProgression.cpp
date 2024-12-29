#include"../headers/LevelProgression.h"

#include <iostream>
#include<algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "../headers/Exceptions.h"

LevelProgression::LevelProgression() {
    progress_bar=this->RoundedRectangle(1920.0f/2-(border_width+4*border_radius)/2,20.0f,border_width,border_height,border_radius,
        sf::Color::Transparent,5.0f,sf::Color::White);
    progress_bar_fill.setFillColor(sf::Color(225, 188, 42));
    progress_bar_fill.setPosition(1920.0f/2-(border_width+4*border_radius)/2 -border_radius*2.0f,20.0f);
    progress_bar_fill.setSize(sf::Vector2f(0.0f,border_height));
    if(!font.loadFromFile("font/game_font.otf")) {
        throw Font_error("Font could not be loaded");
    }
    level_percent.setFont(font);
    level_percent.setCharacterSize(50);
    level_percent.setOutlineColor(sf::Color::Black);
    level_percent.setOutlineThickness(3.0f);
    level_percent.setString(std::to_string(static_cast<int>(percent))+"%");
    level_percent.setPosition(progress_bar.getGlobalBounds().left+border_width+border_radius*4,0.0f);
}

void LevelProgression::updatePercent(double totalDistanceTravelled, double levelLength) {
    percent = std::min((totalDistanceTravelled / levelLength) * 100.0f, 100.0);
    level_percent.setString(std::to_string(static_cast<int>(percent)) + "%");
    double progress_width=(750.0f+2*border_radius)* percent/100.0f;
    // progress_bar_fill=this->RoundedRectangle(500.0f,500.0f,static_cast<float>(progress_width),25.0f,12.5f,
    //         sf::Color::Black,0.0f,sf::Color::Black);
    progress_bar_fill.setSize(sf::Vector2f(static_cast<float>(progress_width),border_height));
}

void LevelProgression::render(sf::RenderWindow &window) {
    window.draw(level_percent);
    window.draw(progress_bar_fill);
    // window.draw(progress_bar_fill);
    window.draw(progress_bar);
}

// void LevelProgression::updatePosition(sf::RenderWindow &window) {
// }

sf::ConvexShape LevelProgression::RoundedRectangle(float pos_x, float pos_y, float rectWidth, float rectHeight,
                                  float radius, const sf::Color& Col, float Outline,
                                  const sf::Color& OutlineCol) {
    //intrucat nu avem posibilitatea de a ne crea dreptunghiuri cu colturi rotunjite in sfml
    //am ales sa creez un convexshape iar fiecare colt sa fie un arc de cerc format din un numar
    //de puncte unite
    const int points = 20;
    sf::ConvexShape rrect;

    rrect.setPointCount(4 * points);

    rrect.setFillColor(Col);
    rrect.setOutlineThickness(Outline);
    rrect.setOutlineColor(OutlineCol);

    double X, Y;
    int index = 0;

    //formula pentru arce este x^2+y^2=r^2
    //x este incrementat cu distanta dintre 2 puncte iar y este scos din formula de sus
    //sau crestem y atunci cand x se deplaseaza de la dreapta la stanga apoi scoatem
    //la final adaugam punctul in functie de coltul in care il adaugam
    // sus-dreapta
    X = 0, Y = 0;
    for (int i = 0; i < points; i++) {
        X+=radius/points;
        Y=sqrt(radius*radius-X*X);
        rrect.setPoint(index++,sf::Vector2f(X+pos_x+rectWidth-radius,pos_y-Y+radius));

    }

    // jos-dreapta
    X = 0, Y = 0;
    for (int i = 0; i < points; i++) {
        Y+=radius/points;
        X=sqrt(radius*radius-Y*Y);
        rrect.setPoint(index++, sf::Vector2f(pos_x + rectWidth - radius + X, pos_y + rectHeight -radius +Y));

    }

    // jos-stanga
    X = 0, Y = 0;
    for (int i = 0; i < points; i++) {
        X+=radius/points;
        Y=sqrt(radius*radius-X*X);
        rrect.setPoint(index++,sf::Vector2f(pos_x-radius-X,pos_y+rectHeight-radius+Y));

    }

    // sus-stanga
    X = 0, Y = 0;
    for (int i = 0; i < points; i++) {
        Y+=radius/points;
        X=sqrt(radius*radius-Y*Y);
        rrect.setPoint(index++,sf::Vector2f(pos_x-radius-X,pos_y+radius-Y));
    }

    return rrect;
}
