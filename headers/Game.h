#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Level.h"
#include "Menu.h"

class Game {
    sf::RenderWindow *window;
    Menu menu;
    sf::Font font;
    sf::Text menuTitle;

    bool isRunningGame;
    bool isInMenu;

    std::unique_ptr<Level> currentLevel;

    void initWindow();
    void startLevel(int levelIndex);
    Game();
public:
    Game(const Game &game)=delete;
    Game& operator=(const Game &game)=delete;
    static Game &getInstanceGame();
    ~Game();
    bool isRunning() const;
    void handleEvents();
    void update();
    void render();
};

#endif // GAME_H

