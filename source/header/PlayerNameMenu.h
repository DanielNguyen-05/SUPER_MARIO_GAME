#pragma once
#include "DEFINITION.h" 
#include "Menu.h"
#include "LevelsList.h"



class PlayerNameMenu : public Menu{
private:
    // Thành phần giao diện
    sf::Text title;
    sf::Text usernameLabel;
    sf::Text inputFieldName;
    sf::Text loginButton;
    sf::String username;
    sf::Text errorMessage;
    bool enterName = true;

public:

    // Constructor
    PlayerNameMenu();

    // Vẽ giao diện
    void draw(sf::RenderWindow& window) override;

    // Make Menu display
	void show(player& newPlayer);

    // Lấy tên người dùng
    //sf::String getName() const;

    // Handle all events happening on Player Name window
    void catchEvents(Event event, player& newPlayer, LevelsList& levelsList);

    // Lưu tên người dùng vào file
    void saveUsernameToFile();

private:
    // Helper functions to handle specific events
    void handleKeyReleased(sf::Keyboard::Key keyCode, player& newPlayer, LevelsList& levelsList);
    void handleBackspace();
    void handleEnter(player& newPlayer, LevelsList& levelsList);
    void handleTextEntered(sf::Uint32 unicode);
    void resetFields();
    void updateInputFields();
    bool isValidInput(const sf::String& Input) const;
    void setErrorMessage(const sf::String& message);
    bool checkCredentials(const sf::String& username);
    void handleMouseClick(sf::Vector2i mousePos, player& newPlayer, Event event);
    void handleLogin(player& newPlayer, LevelsList& levelsList);
};

