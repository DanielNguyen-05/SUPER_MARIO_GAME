#pragma once
#include "DEFINITION.h"
#include "Menu.h"
#include "PlayerNameMenu.h"

class GameMenu : public Menu {
private:
  sf::Font font;
  sf::Text Options[2];
  sf::Text titleText;
  int selectedPlayerOption;
  bool newUser = true;

  bool isHovering(const sf::Text& text, const sf::Vector2i& mousePos);

  // Move up to the previous option
  void moveUp();

  // Move to the next option
  void moveDown();
public:
  PlayerNameMenu user;

  GameMenu();

  // Vẽ giao diện
  void draw(sf::RenderWindow& window) override;

  // Handle all events happening on Player window
  void catchEvents(Event event, player& newPlayer);

  void handleMouseClick(sf::Vector2i mousePos, player& newPlayer, Event event);

  void handleKeyReleased(sf::Keyboard::Key keyCode, player& newPlayer);

  void handleEnter(player& newPlayer);

  // Lưu tên người dùng vào file
  void saveUsernameToFile();
};
