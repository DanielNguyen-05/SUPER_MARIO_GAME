#pragma once
#include "DEFINITION.h" 
#include "Menu.h"

class PlayerNameMenu : public Menu {
private:
    // Thành phần giao diện
    sf::Text title;
    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::Text inputFieldName;
    sf::Text inputFieldPassword;
    sf::Text loginButton;
    sf::Text registerButton;
    sf::String username;
    sf::String password;
    sf::Text errorMessage;
    bool enterName = true;

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
    void updateInputFields();
    bool isValidInput(const sf::String& Input) const;
};