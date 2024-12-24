#pragma once
#include "DEFINITION.h"

class GameOver {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text coinsText;
    sf::Text continueText;
    sf::RectangleShape background;
    sf::RectangleShape border;
    sf::RectangleShape marioBody;
    sf::CircleShape marioHead;
    std::vector<sf::RectangleShape> decorations;
    sf::Clock blinkClock;
    int score;
    int coins;

    void initializeTexts();

    void initializeShapes();

public:
    GameOver(sf::RenderWindow& window, int finalScore, int finalCoins);

    void update();

    void draw();

    bool handleInput();
};