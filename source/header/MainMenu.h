#pragma once
#include "DEFINITION.h"
#include "Menu.h"
#include "../Header/PlayerNameMenu.h"
// #include "../Header/HowToPlayMenu.h"
#include "../header/HighScoreMenu.h"
#include "../Header/OptionsMenu.h"
// #include "../Header/CreditsMenu.h"

class MainMenu : private Menu
{
private: // attributes
    PlayerNameMenu playerName;
    // HowToPlayMenu howToPlay;
    HighScoreMenu highScore;
    OptionsMenu options;
    // CreditsMenu credits;
    sf::Font menuFont;
    sf::Text menuOptions[6];
    sf::Texture optionShadowTexture;
    sf::Text menuOptionsOutline[6];
    int selectedOption;

public: // attributes
    bool gameRunning;
    player newPlayer;
    characterState_t characterState;

private: // methods
    // Draw Main Menu contents
    void draw(sf::RenderWindow& window) override;

    // Handle all events happening on Main Menu
    void catchEvents(sf::Event event) override;

    // Move up to the previous option
    void moveUp();

    // Move to the next option
    void moveDown();

    // Handle what would be done when choosing a specific option
    void mainMenuHandleSelection();

    // Control which music will be started
    void controlMusic();

    // Control enemies' speed according to selected difficulty
    void controlEnemiesSpeed();

    void updateMenuOptionsColors();

public: // methods
    // Constructor
    MainMenu();

    // Control all events happening in Menu and its children
    void handleAllEvents(sf::Event event);

    // Draw Menu and its children contents
    void drawAll(sf::RenderWindow& window);

    // Make Menu display
    void checkShow();
};