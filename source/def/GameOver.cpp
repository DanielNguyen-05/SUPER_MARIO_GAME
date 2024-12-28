#include "../header/GameOver.h"

GameOver::GameOver()
{
    display = false;
    // Set Back Text Properties
	setBackText();

    score = coins = 0;
    if (!font.loadFromFile(GAME_HEADER_FONT))
    {
        throw std::runtime_error("Could not load font");
    }

    // Load background
	if (!backGroundTexture.loadFromFile(FORMAT_BACKGROUND))
	{
		std::cout << "Can't load FORMAT_BACKGROUND\n";
	}
	backGroundSprite.setTexture(backGroundTexture);

    // Game Over Text
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color(255, 69, 0)); // Red-Orange
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition((1600 - gameOverText.getGlobalBounds().width) / 2, 200);

    notification.setPosition((1600 - gameOverText.getGlobalBounds().width) / 2, 300);
	notification.setFont(font);
	notification.setCharacterSize(50);
	notification.setString("PLEASE TRY AGAIN");

    // Score Text
    scoreText.setFont(font);
    scoreText.setString("YOUR SCORE: " + std::to_string(score));
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setStyle(sf::Text::Italic);
    scoreText.setPosition((1600 - scoreText.getGlobalBounds().width) / 2, 400);

    // Coins Text
    coinsText.setFont(font);
    coinsText.setString("COINS COLLECTED: " + std::to_string(coins));
    coinsText.setCharacterSize(50);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setStyle(sf::Text::Italic);
    coinsText.setPosition((1600 - coinsText.getGlobalBounds().width) / 2,470);

}


void GameOver::update(int s, int c)
{
    /*// Blinking effect for continue text
    if (blinkClock.getElapsedTime().asSeconds() >= 0.5f)
    {
        continueText.setFillColor(
            continueText.getFillColor() == sf::Color::White
            ? sf::Color::Transparent
            : sf::Color::White);
        blinkClock.restart();
    }*/
   // Score Text
   score = s;
   coins = c;
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

}

void GameOver::draw(RenderWindow& window, int Score, int Coins)
{
        update(Score, Coins);
        window.clear();
        window.draw(backGroundSprite);
        window.draw(gameOverText);
        window.draw(notification);
        window.draw(scoreText);
        window.draw(coinsText);
}

bool GameOver::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        return true; // Signal to exit game over screen
    }
    return false;
}
