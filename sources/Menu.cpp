#include "../headers/Menu.h"

#include <iostream>

#include "../headers/Exceptions.h"


Menu::Menu(const std::vector<std::string> &options, const sf::RenderWindow &window) {
    float buttonWidth = 300.0f;
    float buttonHeight = 50.0f;
    float startX = (static_cast<float>(window.getSize().x) - buttonWidth) / 2.0f;
    float startY = 500.0f;

    for (long long unsigned int i = 0; i < options.size(); ++i) {
        sf::Vector2f position(startX, startY + static_cast<float>(i)* (buttonHeight + 20.0f));
        buttons.emplace_back(std::make_shared<Button>(options[i], position, sf::Vector2f(buttonWidth, buttonHeight)));
    }
    if (!backgroundTexture.loadFromFile("images/background1-3.png")) {
        throw Texture_error("images/background1-3.png");
    }
    this->backgroundSprite.setTexture(backgroundTexture);
    this->backgroundSprite.setPosition(0.0f, 0.0f);
    this->backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / static_cast<float>(backgroundTexture.getSize().x),
        static_cast<float>(window.getSize().y) / static_cast<float>(backgroundTexture.getSize().y)
    );
    this->backgroundSprite.setColor(sf::Color::Blue);

    if(!this->titleTexture.loadFromFile("images/GeometryDashLogo.png")) {
        throw Texture_error("images/GeometryDashLogo.png");
    }
    this->titleSprite.setTexture(this->titleTexture);
    this->titleSprite.setPosition(static_cast<float>(window.getPosition().x+window.getSize().x)/2.0f,
        static_cast<float>(window.getPosition().y+window.getSize().y)/5.0f);
    if(!songBuffer.loadFromFile("sound/Menu_song.ogg")) {
        throw Sound_error("sound/Menu_song.ogg");
    }
    song.setBuffer(songBuffer);
}
Menu::Menu(const Menu& other)
    : buttons(other.buttons),
      selectedOption(other.selectedOption),
        backgroundTexture(other.backgroundTexture),
        titleTexture(other.titleTexture),
        songBuffer(other.songBuffer)
{
    backgroundTexture.loadFromFile("images/background1-3.png");
    backgroundSprite.setTexture(backgroundTexture);
    titleTexture.loadFromFile("images/GeometryDashLogo.png");
    titleSprite.setTexture(titleTexture);
    songBuffer.loadFromFile("sound/Menu_song.ogg");
    song.setBuffer(songBuffer);
    this->backgroundSprite.setColor(sf::Color::Blue);
    this->titleSprite.setPosition(100.0f,100.0f);

}

Menu& Menu::operator=(const Menu& other) {
    if (this == &other) {
        return *this;
    }

    buttons = other.buttons;
    selectedOption = other.selectedOption;
    backgroundTexture.loadFromFile("images/background1-3.png");
    backgroundSprite.setTexture(backgroundTexture);
    titleTexture.loadFromFile("images/GeometryDashLogo.png");
    titleSprite.setTexture(titleTexture);
    songBuffer.loadFromFile("sound/Menu_song.ogg");
    song.setBuffer(songBuffer);
    this->backgroundSprite.setColor(sf::Color(120,120,250));
    this->titleSprite.setPosition(100.0f,100.0f);
    return *this;
}
void Menu::handleEvent(const sf::Event &event, const sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (unsigned long long int i = 0; i < buttons.size(); ++i) {
            if (buttons[i]->isMouseOver(window)) {
                selectedOption = static_cast<int>(i);
                break;
            }
        }
    }
}
void Menu::render(sf::RenderWindow &window) {
    window.draw(this->backgroundSprite);
    window.draw(this->titleSprite);
    for (auto &button : buttons) {
        button->render(window);
    }
}

void Menu::update(const sf::RenderWindow &window) {
    for (auto &button : buttons) {
        if (button->isMouseOver(window)) {
            button->setColor(sf::Color::Red);
        } else {
            button->setColor(sf::Color::Blue);
        }
    }
}

int Menu::getSelectedOption() const {
    return selectedOption;
}
bool Menu::isOptionSelected() const {
    return selectedOption >= 0;
}

int Menu::getOptionCount() const {
    return static_cast<int>(buttons.size());
}
void Menu::resetOption() {
    selectedOption=-1;
}

void Menu::controlMenuSong(bool state) {
    if (state) {
        song.setLoop(true);
        song.play();
    }
    else {
        song.stop();
    }
}
