#pragma once
#include "DEFINITION.h"
#include "Menu.h"
#include "PlayerNameMenu.h"
#include "LevelsList.h"

class PlayerOptionsMenu : public Menu
{
private:
    sf::Font font;
    sf::Text PlayerOptions[2];
    sf::Text PlayerOptionsOutline[2];
    sf::Text titleText;
    int selectedPlayerOption;
    bool newUser;

    bool isHovering(const sf::Text &text, const sf::Vector2i &mousePos);

    // Move up to the previous option
    void moveUp();

    // Move to the next option
    void moveDown();

    void updatePlayerOptionsColors();

public:
    PlayerNameMenu user;

    LevelsList levelsList;

    std::fstream playersFile;

    PlayerOptionsMenu();

    // Vẽ giao diện
    void draw(sf::RenderWindow &window) override;

    // Handle all events happening on Player window
    void catchEvents(Event event, player &newPlayer);

    void handleMouseClick(sf::Vector2i mousePos, player &newPlayer, Event event);

    void handleKeyReleased(sf::Keyboard::Key keyCode, player &newPlayer);

    void handleEnter(player &newPlayer);

    // Get how many lines in players file
	int getNumberOfLines();

    // Search for player name in files to get his last checkpoint
	void handleLevelsList(player& newPlayer);
};
