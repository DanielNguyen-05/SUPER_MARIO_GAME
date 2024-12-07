#pragma once
#include "DEFINITION.h" 
#include "Menu.h"

class Register : public Menu {
private:
    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::Text inputFieldName;
    sf::Text inputFieldPassword;
    sf::Text loginButton;
    sf::Text registerButton;
    sf::String usernameRegister;
    sf::String passwordRegister;
    sf::Text errorMessage;
    bool enterName = true;

public:
    //Constructor
    Register();

    void show(player& newPlayer);

    void draw(sf::RenderWindow& window) override;

    //handle all event happening on Register window
    void catchEvents(Event event, player& newPlayer);

private:
    void handleKeyReleased(sf::Keyboard::Key keyCode, player& newPlayer);
    void handleBackspace();
    void handleEnter(player& newPlayer);
    void handleTextEntered(sf::Uint32 unicode);
    void resetFields();
    void updateInputFields();
    bool isValidInput(const sf::String& Input) const;
    void setErrorMessage(const sf::String& message);
    bool checkCredentials(const sf::String& username);
    void handleMouseClick(sf::Vector2i mousePos, player& newPlayer);
    void handleRegister(player& newPlayer);
    void handleLogin(player& newPlayer);
};