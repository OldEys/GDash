//
// Created by Babii Victor on 10/18/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"


class Player {
    sf::RectangleShape body;
    sf::Texture texture;
    sf::Sprite sprite;

    public:
    // Player()=default;
    Player();
    ~Player();

    void setPosition(float position);
    void updatePlayer();
    void renderPlayer(sf::RenderWindow &window);


};



#endif //PLAYER_H
