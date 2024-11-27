#include "../header/PlayerNameMenu.h"

// Constructor
PlayerNameMenu::PlayerNameMenu() {
	// Set Back Text Properties
	setBackText();

	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);
	// Set Player Name Text Properties
	playerNameText.setFont(font);
	playerNameText.setCharacterSize(70);
	playerNameText.setStyle(Text::Style::Bold);
	playerNameText.setPosition(447, 411);
	// Ban đầu, menu không hiển thị
	display = false;
}

// Vẽ giao diện
void PlayerNameMenu::draw(sf::RenderWindow& window) {
	if (display) {
		window.draw(backGroundSprite);
		window.draw(playerNameText);
		window.draw(backText);
	}
	//levelsList.draw(window);
}


// Lấy tên người dùng
sf::String PlayerNameMenu::getName() const {
	return username;
}

// Hiển thị menu
void PlayerNameMenu::show() {
	display = true;
}

// Ẩn menu
void PlayerNameMenu::hide() {
	display = false;
}

void PlayerNameMenu::catchEvents(Event event, player& newPlayer) {
	if (display) {
		switch (event.type)
		{
		case Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Backspace:
				// Erase last character form string
				username = username.substring(0, username.getSize() - 1);
				playerNameText.setString(username);
				changingOptionSound.play();
				break;
			case sf::Keyboard::Enter:
				if (!username.isEmpty()) {
					this->hide();

					// Convert sfml String to std String
					newPlayer.name = std::string(username);

					username = ""; // To Clean last inputed name
					playerNameText.setString(username);

					//levelsList.show(newPlayer);
				}
				changingOptionSound.play();
				break;
			case Keyboard::Escape:
				this->hide();
				changingOptionSound.play();
				break;
			}
			break;

		case Event::TextEntered:
			bool notForbidinKeys = (!Keyboard::isKeyPressed(Keyboard::Enter) && !Keyboard::isKeyPressed(Keyboard::BackSpace)) && (!Keyboard::isKeyPressed(Keyboard::Escape) && !Keyboard::isKeyPressed(Keyboard::Space));
			if (username.getSize() <= 20 && notForbidinKeys) {
				if (event.text.unicode < '0' || event.text.unicode > '9')
					username += event.text.unicode;
				playerNameText.setString(username);
			}
			break;
		}
	}
	//levelsList.catchEvents(event, newPlayer);
}