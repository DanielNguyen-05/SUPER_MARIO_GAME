#pragma once
#include "DEFINITION.h" 
#include "Menu.h"

class PlayerNameMenu : public Menu {
private:
    // Thành phần giao diện
    sf::Text playerNameText;
    sf::String username;

public:
    // Constructor
    PlayerNameMenu();

    // Vẽ giao diện
    void draw(sf::RenderWindow& window) override;

    // Lấy tên người dùng
    sf::String getName() const;

    // Handle all events happening on Player Name window
    void catchEvents(Event event, player& newPlayer);

private:
    // Helper functions to handle specific events
    void handleKeyReleased(sf::Keyboard::Key keyCode, player& newPlayer);
    void handleBackspace();
    void handleEnter(player& newPlayer);
    void handleTextEntered(sf::Uint32 unicode);
};