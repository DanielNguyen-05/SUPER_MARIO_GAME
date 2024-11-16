#include "../header/Start.h"

Start::Start()
{
    // Load background image
    if (!backgroundTexture.loadFromFile("../../assets/backgrounds/02.png"))
    {
        cerr << "Failed to load background image!" << "\n";
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
    }

    // Load font
    if (!font.loadFromFile("../../assets/fonts/Super_Mario_Bros.ttf"))
    {
        cerr << "Failed to load font!" << "\n";
    }

    // Create buttons
    playButton = Button(300, 200, 200, 50, &font, "Play", sf::Color::Blue, sf::Color::Green, sf::Color::Red);
    optionsButton = Button(300, 300, 200, 50, &font, "Options", sf::Color::Green, sf::Color::Green, sf::Color::Red);
    exitButton = Button(300, 400, 200, 50, &font, "Exit", sf::Color::Red, sf::Color::Green, sf::Color::Red);

    gameStarted = false;
}

void Start::render(sf::RenderTarget* target)
{
    // Draw the background
    target->draw(backgroundSprite);

    // Load font and display welcome text
    sf::Font font;
    if (!font.loadFromFile("../../assets/fonts/Super_Mario_Bros.ttf"))
    {
        cerr << "Failed to load font!" << "\n";
    }
    else
    {
        sf::Text text("WELCOME TO SUPER MARIO GAME !!!", font, 30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(100, 100);
        target->draw(text);
    }

    // Draw buttons
    playButton.render(target);
    optionsButton.render(target);
    exitButton.render(target);
}

bool Start::isGameStarted() const
{
    return gameStarted;
}

void Start::handleMouseClick(sf::RenderWindow& window)
{
    if (playButton.isMouseOver(window))
    {
        gameStarted = true; // Start the game
    }
    if (exitButton.isMouseOver(window))
    {
        window.close(); // Exit the game
    }
    if (optionsButton.isMouseOver(window))
    {
        // Handle options (chưa có logic)
    }
}
