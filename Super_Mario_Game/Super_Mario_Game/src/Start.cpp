#include "Start.h"

Start::Start() : gameStarted(false) {
    // Load the background texture
    if (!backgroundTexture.loadFromFile("assets/backgrounds/01.png")) {
        cerr << "Failed to load background texture!" << "\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Start::draw(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Super_Mario_Bros.ttf")) {
        cerr << "Failed to load font!" << "\n";
    } else {
        sf::Text text("WELCOME TO SUPER MARIO GAME !!!", font, 30);
        text.setFillColor(sf::Color::Black);
        text.setPosition(200, 500);
        window.draw(text);
    }
    window.draw(backgroundSprite);
}

bool Start::isGameStarted() const {
    return gameStarted;
}
