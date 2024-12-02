#pragma once
#include "Button.h"
class Start {
private:
    bool gameStarted;
    sf::Font font; // Declare the font variable
    Button playButton; // Assuming you have defined Button properly
    Button optionsButton;
    Button exitButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
public:
    Start();

    void render(sf::RenderTarget* target);
    bool isGameStarted() const;
    // void handleMouseClick(sf::RenderWindow& window);
    sf::Font getFont() const { return font; }
};

