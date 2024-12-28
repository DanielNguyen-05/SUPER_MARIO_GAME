#pragma once
#include "DEFINITION.h"
#include"Menu.h"

class Winner : public Menu {
private:
    sf::Font font;
    sf::Text WinnerText;
    sf::Text scoreText;
    sf::Text coinsText;
    sf::Text notification;
    int score, coins;


public:
    bool display;
    Winner();

    void update(int score, int coins);

    void draw(RenderWindow& window, int , int);
};