#include "../header/PlayerNameMenu.h"

// Constructor
PlayerNameMenu::PlayerNameMenu() {
	// ban đầu cho menu hiển thị
	this->hide();

	// Set Back Text Properties
	setBackText();
	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	usernameLabel.setFont(font);
	usernameLabel.setString("Enter your username:");
	usernameLabel.setCharacterSize(50);
	usernameLabel.setFillColor(sf::Color::White);
	usernameLabel.setPosition(400, 350);

	inputFieldName.setFont(font);
	inputFieldName.setString("_");
	inputFieldName.setCharacterSize(40);
	inputFieldName.setFillColor(sf::Color::Green);
	inputFieldName.setPosition(400, 410);

	loginButton.setFont(font);
	loginButton.setString("Login");
	loginButton.setCharacterSize(40);
	loginButton.setFillColor(sf::Color::Red);
	loginButton.setPosition(750, 550);

	errorMessage.setFont(font);
	errorMessage.setCharacterSize(30);
	errorMessage.setFillColor(sf::Color::Red);
	errorMessage.setPosition(600, 500);
	errorMessage.setString("");  // Ban đầu để trống

}

// Vẽ giao diện
void PlayerNameMenu::draw(sf::RenderWindow& window) {
	if (display) {
		window.draw(backGroundSprite);
		window.draw(usernameLabel);
		window.draw(inputFieldName);
		window.draw(loginButton);
		window.draw(errorMessage);
		window.draw(backText);
	}
}

// Lấy tên người dùng
/*sf::String PlayerNameMenu::getName() const {
	return username;
}*/

void PlayerNameMenu::catchEvents(Event event, player& newPlayer) {
	if (display) {
		switch (event.type) {
		case Event::KeyReleased:
			handleKeyReleased(event.key.code, newPlayer);
			break;

		case Event::TextEntered:
			handleTextEntered(event.text.unicode);
			break;

		case Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) {
				handleMouseClick({ event.mouseButton.x, event.mouseButton.y }, newPlayer, event);
			}
			break;

		default:
			break;

		}
	}
}

void PlayerNameMenu::handleKeyReleased(sf::Keyboard::Key keyCode, player& newPlayer) {
	switch (keyCode) {
	case sf::Keyboard::Backspace:
		handleBackspace();
		break;

	case sf::Keyboard::Enter:
		handleEnter(newPlayer);
		break;

	case sf::Keyboard::Escape:
		this->hide();
		changingOptionSound.play();
		break;

	default:
		break;
	}
}

void PlayerNameMenu::handleBackspace() {
	// Erase the last character if the string is not empty
	if (enterName) {
		if (!username.isEmpty()) {
			username.erase(username.getSize() - 1);
		}
	}
	changingOptionSound.play();
	updateInputFields();
}

void PlayerNameMenu::handleEnter(player& newPlayer) {
	if (!username.isEmpty()) {
		handleLogin(newPlayer);
		changingOptionSound.play();
	}
}

void PlayerNameMenu::handleTextEntered(sf::Uint32 unicode) {
	if (unicode == '\b') return;  // Bỏ qua Backspace (đã xử lý riêng)

	if (unicode >= 32 && unicode <= 126) {  // Ký tự có thể in được
		if (enterName) {
			username += static_cast<char>(unicode);
		}
	}
	updateInputFields();
}

bool PlayerNameMenu::isValidInput(const sf::String& input) const {
	// Kiểm tra nếu chuỗi chứa bất kỳ khoảng trắng nào
	for (size_t i = 0; i < input.getSize(); ++i) {
		if (std::isspace(input[i])) {
			return false;
		}
	}
	return !input.isEmpty();  // Đảm bảo chuỗi không rỗng
}

void PlayerNameMenu::resetFields() {
	username = "";
	setErrorMessage("");
	enterName = true;  // Quay lại nhập tên người dùng
	updateInputFields();
}


void PlayerNameMenu::updateInputFields() {
	inputFieldName.setString(username + (enterName ? "_" : ""));
}

bool PlayerNameMenu::checkCredentials(const sf::String& username) {
	std::ifstream file(ACCOUNT_FILE);
	if (!file.is_open()) {
		setErrorMessage("Error opening user file!");
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string storedUsername;
		if (iss >> storedUsername) {
			if (username == storedUsername) {
				return false;
			}
		}
	}
	return true;
}

void PlayerNameMenu::setErrorMessage(const sf::String& message) {
	errorMessage.setString(message);
}

void PlayerNameMenu::handleMouseClick(sf::Vector2i mousePos, player& newPlayer, Event event) {
	if (display) {
		// Kiểm tra nếu nhấn nút Login
		if (loginButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			handleLogin(newPlayer);
		}
	}
}

void PlayerNameMenu::handleLogin(player& newPlayer) {
	if (!isValidInput(username)) {
		resetFields();
		setErrorMessage("Invalid username! Spaces not allowed");
	}
	else
	{
		if (checkCredentials(username)) {
			setErrorMessage("Login successful!");
			this->hide();
			newPlayer.username = std::string(username);
			saveUsernameToFile();
			resetFields();
		}
		else {
			//continue or new game menu
		}
		changingOptionSound.play();
	}
}

void PlayerNameMenu::saveUsernameToFile(){
	std::ofstream outFile(ACCOUNT_FILE, std::ios::app); // Mở tệp ở chế độ thêm dữ liệu
    if (outFile.is_open()) {
        outFile << "\n" << username.toAnsiString(); // Ghi tên người dùng vào tệp
        outFile.close();
    } else {
        // Xử lý lỗi nếu không thể mở tệp
        setErrorMessage("Unable to open file to save username.");
    }
}

