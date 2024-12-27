#include "../header/GameOver.h"

void GameOver::initializeTexts() {
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
        throw std::runtime_error("Could not load font");
    }

    // Game Over Text
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(
        (1600 - gameOverText.getGlobalBounds().width) / 2,
        300
    );

    // Score Text
    scoreText.setFont(font);
    scoreText.setString("SCORE: " + std::to_string(score));
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(700, 450);

    // Coins Text
    coinsText.setFont(font);
    coinsText.setString("COINS: " + std::to_string(coins));
    coinsText.setCharacterSize(40);
    coinsText.setFillColor(sf::Color::White);
    coinsText.setPosition(700, 500);

    // Continue Text
    continueText.setFont(font);
    continueText.setString("PRESS SPACE TO CONTINUE");
    continueText.setCharacterSize(30);
    continueText.setFillColor(sf::Color::White);
    continueText.setPosition(
        (1600 - continueText.getGlobalBounds().width) / 2,
        600
    );
}

void GameOver::initializeShapes() {
    // Background
    background.setSize(sf::Vector2f(1600, 900));
    background.setFillColor(sf::Color::Black);

    // Border
    border.setSize(sf::Vector2f(1200, 675));
    border.setPosition(200, 112.5);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(8);
    border.setOutlineColor(sf::Color::White);

    // Mario character (simplified)
    marioHead.setRadius(40);
    marioHead.setFillColor(sf::Color::Red);
    marioHead.setPosition(750, 150);

    charBody.setSize(sf::Vector2f(100, 20));
    charBody.setFillColor(sf::Color::Red);
    charBody.setPosition(720, 240);

    // Bottom decorations
    for (int i = 0; i < 5; i++) {
        sf::RectangleShape decoration;
        decoration.setSize(sf::Vector2f(16, 16));
        decoration.setFillColor(sf::Color::Yellow);

        // Left side decorations
        sf::RectangleShape leftDec = decoration;
        leftDec.setPosition(220 + (i * 24), 750);
        decorations.push_back(leftDec);

        // Right side decorations
        sf::RectangleShape rightDec = decoration;
        rightDec.setPosition(1300 + (i * 24), 750);
        decorations.push_back(rightDec);
    }
}

// Chỗ này thì lấy cái score và coins của người dùng truyền vô, này tao truyền mặc định 12350 và 47
GameOver::GameOver(sf::RenderWindow& window, int finalScore = 12350, int finalCoins = 47)
    : window(window), score(finalScore), coins(finalCoins) {
    initializeTexts();
    initializeShapes();
}

void GameOver::update() {
    // Blinking effect for continue text
    if (blinkClock.getElapsedTime().asSeconds() >= 0.5f) {
        continueText.setFillColor(
            continueText.getFillColor() == sf::Color::White
            ? sf::Color::Transparent
            : sf::Color::White
        );
        blinkClock.restart();
    }
}

void GameOver::draw() {
    window.draw(background);
    window.draw(border);
    window.draw(marioHead);
    window.draw(charBody);
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(coinsText);
    window.draw(continueText);

    for (const auto& decoration : decorations) {
        window.draw(decoration);
    }
}

bool GameOver::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        return true;  // Signal to exit game over screen
    }
    return false;
}
