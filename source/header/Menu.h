#pragma once
#include "DEFINITION.h"

class Menu
{
protected:
    // Set Back Text Properties
    virtual void setBackText();

    // Set Changing Option Sound Properties
    virtual void setChangeOptionSound();

public:
    // Some attributes should be public for easy access
    bool display;
    sf::Font font;
    sf::Text backText;
    sf::Texture backGroundTexture;
    sf::Sprite backGroundSprite;
    sf::SoundBuffer changingOptionBuffer;
    sf::Sound changingOptionSound;

    // Draw Menu Options
    virtual void draw(sf::RenderWindow &window);

    // Control Menu events
    virtual void catchEvents(sf::Event event);

    // Make Menu display
    virtual void show(); // virtual function to be overridden when want to show high score

    // Close Menu
    virtual void hide();
};
