#include "../header/PlayerNameMenu.h"

// Constructor
PlayerNameMenu::PlayerNameMenu() {
	// ban đầu cho menu hiển thị
	display = true;

	// Set Back Text Properties
	setBackText();
	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);

	usernameLabel.setFont(font);
	usernameLabel.setString("Enter your username:");
	usernameLabel.setCharacterSize(40);
	usernameLabel.setFillColor(sf::Color::White);
	usernameLabel.setPosition(400, 270);

	inputFieldName.setFont(font);
	inputFieldName.setString("_");
	inputFieldName.setCharacterSize(40);
	inputFieldName.setFillColor(sf::Color::Green);
	inputFieldName.setPosition(400, 330);

	passwordLabel.setFont(font);
	passwordLabel.setString("Enter your password:");
	passwordLabel.setCharacterSize(40);
	passwordLabel.setFillColor(sf::Color::White);
	passwordLabel.setPosition(400, 390);

	inputFieldPassword.setFont(font);
	inputFieldPassword.setString("_");
	inputFieldPassword.setCharacterSize(40);
	inputFieldPassword.setFillColor(sf::Color::Green);
	inputFieldPassword.setPosition(400, 450);

	loginButton.setFont(font);
	loginButton.setString("Login");
	loginButton.setCharacterSize(40);
	loginButton.setFillColor(sf::Color::Red);
	loginButton.setPosition(750, 550);

	registerButton.setFont(font);
	registerButton.setString("Register");
	registerButton.setCharacterSize(40);
	registerButton.setFillColor(sf::Color::Red);
	registerButton.setPosition(730, 620);

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
		window.draw(passwordLabel);
		window.draw(inputFieldPassword);
		window.draw(loginButton);
		window.draw(registerButton);
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
                handleMouseClick({event.mouseButton.x, event.mouseButton.y}, newPlayer, event);
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

			// case sf::Keyboard::Escape:
			// 	this->hide();
			// 	changingOptionSound.play();
			// 	break;

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
	else {
		if (!password.isEmpty()) {
			password.erase(password.getSize() - 1);
		}
	}
	changingOptionSound.play();
	updateInputFields();
}

void PlayerNameMenu::handleEnter(player& newPlayer) {
	if (!username.isEmpty()) {
		if (enterName) {
			enterName = false;  // Chuyển sang nhập mật khẩu
		}
		else {
			if (checkCredentials(username, password)) {
				newPlayer.username = std::string(username);
				newPlayer.password = std::string(password);
				setErrorMessage("Login successful!.");
				this->hide();
			}
			else {
				setErrorMessage("Incorrect username or password!");
			}
			resetFields();
		}
	}
	updateInputFields();
	changingOptionSound.play();
}

void PlayerNameMenu::handleTextEntered(sf::Uint32 unicode) {
	if (unicode == '\b') return;  // Bỏ qua Backspace (đã xử lý riêng)

	if (unicode >= 32 && unicode <= 126) {  // Ký tự có thể in được
		if (enterName) {
			username += static_cast<char>(unicode);
		}
		else {
			password += static_cast<char>(unicode);
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
	password = "";
	enterName = true;  // Quay lại nhập tên người dùng
	updateInputFields();
}


void PlayerNameMenu::updateInputFields() {
	inputFieldName.setString(username + (enterName ? "_" : ""));
	inputFieldPassword.setString(std::string(password.getSize(), '*'));
}

bool PlayerNameMenu::checkCredentials(const sf::String& username, const sf::String& password) {
	std::ifstream file(ACCOUNT_FILE);
	if (!file.is_open()) {
		setErrorMessage("Error opening user file!");
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string storedUsername, storedPassword;

		// Tách username và password từ dòng
		if (iss >> storedUsername >> storedPassword) {
			if (username == storedUsername && password == storedPassword) {
				return true;  // Đăng nhập thành công
			}
		}
	}
	return false;  // Không tìm thấy thông tin khớp
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

        // Kiểm tra nếu nhấn nút Register
        if (registerButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            handleRegister(event, newPlayer);
        }
    }
}

void PlayerNameMenu::handleLogin(player& newPlayer) {
    if (checkCredentials(username, password)) {
        setErrorMessage("Login successful!");
        this->hide();
        newPlayer.username = std::string(username);
        newPlayer.password = std::string(password);
    } else {
        setErrorMessage("Incorrect username or password!");
        resetFields();
    }
    changingOptionSound.play();
}

void PlayerNameMenu::handleRegister(Event event, player& newPlayer) {
	this->hide();
	R.show(newPlayer);
    changingOptionSound.play();
}
