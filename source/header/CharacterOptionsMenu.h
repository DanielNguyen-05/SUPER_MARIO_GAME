#pragma once
#include "DEFINITION.h"
#include "Menu.h"

class CharacterOptionsMenu : public Menu
{
private:
    sf::Font font;
    sf::Text characterOptions[2];
    sf::Text characterOptionsOutline[2];
    sf::Text titleText;
    int selectedCharacterOption;
    bool newUser;

    // Move up to the previous option
    void moveUp();

    // Move to the next option
    void moveDown();

    void updateCharacterOptionsColors();

public:
    CharacterOptionsMenu();

    // Vẽ giao diện
    void draw(sf::RenderWindow &window) override;

    // Handle all events happening on Character window
    void catchEvents(Event event) override;

    void handleKeyReleased(sf::Keyboard::Key keyCode);

    void handleEnter();
};