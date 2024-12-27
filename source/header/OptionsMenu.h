#pragma once
#include "DEFINITION.h"
#include "Menu.h"

class OptionsMenu : public Menu
{
private:
    // Properties
    sf::Texture optionShadowTexture;
    sf::Texture musicBallTexture;
    sf::Texture controlBallTexture;
    sf::Sprite optionShadowSprite;
    sf::Sprite musicBallSprite;
    sf::Sprite controlBallSprite;
    sf::SoundBuffer menuBuffer, levelBuffer;
    int activeSlide;

public:
    sf::Sound menuSound, levelSound;
    bool muteMusic, handControlled;

    // Constructors
    OptionsMenu();

    /***        Methods         ***/
    void draw(sf::RenderWindow &window) override;
    void catchEvents(sf::Event event, player &newPlayer);
    void moveRight();
    void moveLeft();
    void changeSettings(bool up, player &newPlayer);
    void changeActiveMusicOption();   // Change Music ball (on and off)
    void updateMusicSettings();       // mute or unmute music
    void changeActiveControlOption(); // Change Control ball (hand or keyboard)
    void updateControlSettings();     // Change control settings
};