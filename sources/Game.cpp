#include "../headers/Game.h"
#include <iostream>

#include "../headers/Exceptions.h"

Game::Game()
    : window(nullptr), isRunningGame(true), isInMenu(true), currentLevel(nullptr) {
    this->initWindow();
    std::vector<std::string> menuOptions = {"Play Level 1", "Play Level 2", "Play Level 3", "Exit"};
    //in functie de cate nivele dorim adaugam elemente noi pentru a crea butoane noi
    menu = Menu(menuOptions, *window);
    menu.controlMenuSong(true);
}

Game &Game::getInstanceGame() {
    static Game instance;
    return instance;
}

Game::~Game() {
    delete window;
}
void Game::initWindow() {
    sf::VideoMode videoMode(1920, 1080);
    this->window = new sf::RenderWindow(videoMode, "GDash", sf::Style::Default);
    this->window->setFramerateLimit(60);
    this->window->setPosition(sf::Vector2i(0, 0));
}

bool Game::isRunning() const {
    return this->isRunningGame && this->window->isOpen();
}

void Game::startLevel(int levelIndex) {
    if (levelIndex == 0) {
        currentLevel = std::make_unique<Level>("sound/Level1_soundtrack.ogg", "maps/obstacole1.in", *window,
                                               sf::Color(100, 100, 255));
    } else if (levelIndex == 1) {
        currentLevel = std::make_unique<Level>("sound/Level2_soundtrack.ogg", "maps/obstacole2.in", *window,
                                               sf::Color(252, 48, 232));
    } else if (levelIndex == 2) {
        currentLevel = std::make_unique<Level>("sound/Level3_soundtrack.ogg", "maps/obstacole3.in", *window,
                                               sf::Color(51, 161, 55));
    } else {
        throw InvalidLevelIndex_error(std::to_string(levelIndex))
    }
    //pentru a extinde gameplayul nu avem decat sa adaugam in continuare nivele
    //cu alt soundtrack ,mapa si culoare a nivelului
    if (!currentLevel) {
        std::cerr << "Eroare: Nu s-a putut crea nivelul!" << std::endl;
        isInMenu = true;
        return;
    }

    isInMenu = false;
    currentLevel->startLevelLogic();
}

void Game::handleEvents() {
    sf::Event event;
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunningGame = false;
        }

        if (isInMenu) {
            menu.handleEvent(event, *window);
            window->setView(window->getDefaultView());
            if (menu.isOptionSelected()) {
                long long unsigned int selectedMenuOption = menu.getSelectedOption();
                if (static_cast<int>(selectedMenuOption) == menu.getOptionCount() - 1) {
                    isRunningGame = false;
                    //exit
                } else {
                    isInMenu = false;
                    menu.controlMenuSong(false);
                    startLevel(static_cast<int>(selectedMenuOption));
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                isRunningGame = false;
            }
        } else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                if (currentLevel)
                    currentLevel->stopLevel();
                isInMenu = true;
                menu.resetOption();
                menu.controlMenuSong(true);
            }
        }
    }
}

void Game::update() {
    if (isInMenu) {
        menu.update(*window);
    } else if (currentLevel) {
        currentLevel->update(*window);
    }
}


void Game::render() {
    window->clear();
    if (isInMenu) {
        menu.render(*window);
    } else {
        currentLevel->render(*window);
    }

    window->display();
}