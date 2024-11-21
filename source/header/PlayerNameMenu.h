#pragma once
#include "DEFINITION.h" 
#include "Menu.h"
class PlayerNameMenu : private Menu {
private:
    // Thành phần giao diện
   	sf::Text playerNameText;
	sf::String username;

public:
    bool display;
    void show();
    void hide();
    // Constructor
    PlayerNameMenu();

    // Vẽ giao diện
    void draw(sf::RenderWindow& window) override;

    // Lấy tên người dùng
    sf::String getName() const;
    	//Handle all event happend on Player Name window
	void catchEvents(Event event, player& newPlayer);
};
