#ifndef MENU_H
#define MENU_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include <SFML/Audio.hpp>

class Menu {
    std::vector<std::shared_ptr<Button>> buttons;
    int selectedOption = -1;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture titleTexture;
    sf::Sprite titleSprite;
    sf::SoundBuffer songBuffer;
    sf::Sound song;
public:
    Menu()=default;
    ~Menu()=default;
    Menu(const std::vector<std::string> &options, const sf::RenderWindow &window);
    Menu(const Menu& other);
    Menu& operator=(const Menu& other);

    void handleEvent(const sf::Event &event, const sf::RenderWindow &window);

    void render(sf::RenderWindow &window);
    void update(const sf::RenderWindow &window);
    int getSelectedOption() const;

    bool isOptionSelected() const;

    int getOptionCount()const;

    void resetOption();

    void controlMenuSong(bool state);
};

#endif
