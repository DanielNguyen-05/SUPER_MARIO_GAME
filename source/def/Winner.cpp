#include "../header/Winner.h"

Winner::Winner()
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
    WinnerText.setFont(font);
    WinnerText.setString("Winner");
    WinnerText.setCharacterSize(100);
    WinnerText.setFillColor(sf::Color(255, 69, 0)); // Red-Orange
    WinnerText.setStyle(sf::Text::Bold);
    WinnerText.setPosition((1600 - WinnerText.getGlobalBounds().width) / 2, 200);

    notification.setPosition((700 - WinnerText.getGlobalBounds().width) / 2, 350);
	notification.setFont(font);
	notification.setCharacterSize(50);
	notification.setString("congratulations on the victory");

    // Score Text
    scoreText.setFont(font);
    scoreText.setString("YOUR SCORE: " + std::to_string(score));
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setStyle(sf::Text::Italic);
    scoreText.setPosition((1600 - scoreText.getGlobalBounds().width) / 2, 500);

    // Coins Text
    coinsText.setFont(font);
    coinsText.setString("COINS COLLECTED: " + std::to_string(coins));
    coinsText.setCharacterSize(50);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setStyle(sf::Text::Italic);
    coinsText.setPosition((1600 - coinsText.getGlobalBounds().width) / 2,650);

}


void Winner::update(int s, int c)
{
   // Score Text
   score = s;
   coins = c;
    scoreText.setFont(font);
    scoreText.setString("Total Score: " + std::to_string(score));
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setStyle(sf::Text::Italic);
    scoreText.setPosition(
        (1600 - scoreText.getGlobalBounds().width) / 2,
        500);

    // Coins Text
    coinsText.setFont(font);
    coinsText.setString("COINS COLLECTED: " + std::to_string(coins));
    coinsText.setCharacterSize(50);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setStyle(sf::Text::Italic);
    coinsText.setPosition(
        (1600 - coinsText.getGlobalBounds().width) / 2,
        650);

}

void Winner::draw(RenderWindow& window, int Score, int Coins)
{
    update(Score, Coins);


    Clock clock;
    

    while (clock.getElapsedTime().asSeconds() < 5) {
        window.clear(); 
        window.draw(backGroundSprite);
        window.draw(WinnerText);
        window.draw(notification);
        window.draw(scoreText);
        //window.draw(coinsText);
        window.display();
    }
}


