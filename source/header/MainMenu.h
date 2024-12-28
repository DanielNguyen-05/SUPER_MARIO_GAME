#pragma once
#include "DEFINITION.h"
#include "Menu.h"
#include "PlayerOptionsMenu.h"
#include "HowToPlayMenu.h"
#include "HighScoreMenu.h"
#include "OptionsMenu.h"
#include "CreditsMenu.h"

class MainMenu : private Menu
{
private: // attributes
    PlayerOptionsMenu playerOptions;
    HowToPlayMenu howToPlay;
    HighScoreMenu highScore;
    OptionsMenu options;
    CreditsMenu credits;
    sf::Font menuFont;
    sf::Text menuOptions[6];
    sf::Texture optionShadowTexture;
    sf::Text menuOptionsOutline[6];
    int selectedOption;
    sf::Sprite optionShadowSprite;
    CharacterTypeEnum selectedCharacterType;

    // Singleton attribute
    static MainMenu *instance;

    // Constructor
    MainMenu();

public: // attributes
    bool gameRunning;
    player newPlayer;
    CharacterStateEnum characterState;
    CharacterTypeEnum getSelectedCharacterType() const;

private: // methods
    // Draw Main Menu contents
    void draw(sf::RenderWindow &window) override;

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
    static MainMenu *getInstance();
    MainMenu(const MainMenu &) = delete;
    MainMenu &operator=(const MainMenu &) = delete;

    // Control all events happening in Menu and its children
    void handleAllEvents(sf::Event event);

    // Draw Menu and its children contents
    void drawAll(sf::RenderWindow &window);

    // Make Menu display
    void checkShow();

    void confirmExit();
};
