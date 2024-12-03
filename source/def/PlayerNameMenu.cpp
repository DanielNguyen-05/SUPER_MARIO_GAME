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

void PlayerNameMenu::catchEvents(Event event, player& newPlayer) {
	if (display) {
		switch (event.type) {
		case Event::KeyReleased:
			switch (event.key.code) {
			case sf::Keyboard::Backspace:
				// Erase the last character if the string is not empty
				if (!username.isEmpty()) {
					username = username.substring(0, username.getSize() - 1);
					playerNameText.setString(username);
				}
				changingOptionSound.play();
				break;

			case sf::Keyboard::Enter:
				if (!username.isEmpty()) {
					this->hide();
					newPlayer.name = std::string(username); // Convert sf::String to std::string
					username = ""; // Clear the username for the next input
					playerNameText.setString(username);
				}
				changingOptionSound.play();
				break;

			case sf::Keyboard::Escape:
				this->hide();
				changingOptionSound.play();
				break;

			default:
				break;
			}
			break;

		case Event::TextEntered:
			// Ensure only valid characters are entered (letters, numbers, spaces)
			if (event.text.unicode < 128 && username.getSize() < 20) { // ASCII characters only
				char enteredChar = static_cast<char>(event.text.unicode);
				if (std::isalnum(enteredChar) || enteredChar == ' ') { // Letters, digits, or spaces
					username += enteredChar;
					playerNameText.setString(username);
				}
			}
			break;

		default:
			break;
		}
	}
	//levelsList.catchEvents(event, newPlayer);
}
