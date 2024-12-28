#include "../header/GameOver.h"

void GameOver::initializeTexts()
{
    if (!font.loadFromFile("SuperMarioFont.ttf"))
    {
        throw std::runtime_error("Could not load font");
    }

    // Game Over Text
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color(255, 69, 0)); // Red-Orange
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(
        (1600 - gameOverText.getGlobalBounds().width) / 2,
        200);

    // Score Text
    scoreText.setFont(font);
    scoreText.setString("YOUR SCORE: " + std::to_string(score));
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setStyle(sf::Text::Italic);
    scoreText.setPosition(
        (1600 - scoreText.getGlobalBounds().width) / 2,
        400);

    // Coins Text
    coinsText.setFont(font);
    coinsText.setString("COINS COLLECTED: " + std::to_string(coins));
    coinsText.setCharacterSize(50);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setStyle(sf::Text::Italic);
    coinsText.setPosition(
        (1600 - coinsText.getGlobalBounds().width) / 2,
        470);

    // Continue Text
    continueText.setFont(font);
    continueText.setString("PRESS SPACE TO CONTINUE");
    continueText.setCharacterSize(40);
    continueText.setFillColor(sf::Color(173, 216, 230)); // Light Blue
    continueText.setPosition(
        (1600 - continueText.getGlobalBounds().width) / 2,
        700);
}

void GameOver::initializeShapes()
{
    // Background with gradient-like effect
    background.setSize(sf::Vector2f(1600, 900));
    background.setFillColor(sf::Color(0, 0, 139)); // Dark Blue

    // Border with rounded corners
    border.setSize(sf::Vector2f(1200, 675));
    border.setPosition(200, 112.5);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(10);
    border.setOutlineColor(sf::Color::White);

    // Mario character
    charHead.setRadius(50);
    charHead.setFillColor(sf::Color::Red);
    charHead.setPosition(775, 100);

    charBody.setSize(sf::Vector2f(120, 25));
    charBody.setFillColor(sf::Color(0, 128, 0)); // Green
    charBody.setPosition(740, 180);

    // Bottom decorations - bricks
    sf::Texture brickTexture;
    if (!brickTexture.loadFromFile("brick.png"))
    {
        throw std::runtime_error("Could not load brick texture");
    }

    for (int i = 0; i < 20; i++)
    {
        sf::RectangleShape brick;
        brick.setSize(sf::Vector2f(32, 32));
        brick.setTexture(&brickTexture);

        // Bottom row bricks
        brick.setPosition(200 + (i * 60), 850);
        decorations.push_back(brick);
    }
}

// Chỗ này thì lấy cái score và coins của người dùng truyền vô, này tao truyền mặc định 12350 và 47
GameOver::GameOver(sf::RenderWindow& window, int finalScore = 12350, int finalCoins = 47)
    : window(window), score(finalScore), coins(finalCoins)
{
    initializeTexts();
    initializeShapes();
}

void GameOver::update()
{
    // Blinking effect for continue text
    if (blinkClock.getElapsedTime().asSeconds() >= 0.5f)
    {
        continueText.setFillColor(
            continueText.getFillColor() == sf::Color::White
            ? sf::Color::Transparent
            : sf::Color::White);
        blinkClock.restart();
    }
}

void GameOver::draw()
{
    window.draw(background);
    window.draw(border);
    window.draw(charHead);
    window.draw(charBody);
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(coinsText);
    window.draw(continueText);

    for (const auto& decoration : decorations)
    {
        window.draw(decoration);
    }
}

bool GameOver::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        return true; // Signal to exit game over screen
    }
    return false;
}
