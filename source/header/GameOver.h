#pragma once
#include "DEFINITION.h"
#include"Menu.h"

class GameOver : public Menu {
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text coinsText;
    sf::Text notification;
    int score, coins;


public:
    bool display;
    GameOver();

    void update(int score, int coins);

    void draw(RenderWindow& window, int , int);

    bool handleInput();
};