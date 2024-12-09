#include "../header/Register.h"

// Constructor
Register::Register() {
	// ban đầu không cho menu hiển thị
	this->hide();

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

	registerButton.setFont(font);
	registerButton.setString("Register");
	registerButton.setCharacterSize(40);
	registerButton.setFillColor(sf::Color::Red);
	registerButton.setPosition(730, 550);

	loginButton.setFont(font);
	loginButton.setString("Login");
	loginButton.setCharacterSize(40);
	loginButton.setFillColor(sf::Color::Red);
	loginButton.setPosition(750, 620);

	errorMessage.setFont(font);
	errorMessage.setCharacterSize(30);
	errorMessage.setFillColor(sf::Color::Red);
	errorMessage.setPosition(600, 500);
	errorMessage.setString("");  // Ban đầu để trống

}

// Vẽ giao diện
void Register::draw(sf::RenderWindow& window) {
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

void Register::show(player& newPlayer) {
	display = true;
}

// Lấy tên người dùng
//sf::String PlayerNameMenu::getName() const {
//	return username;
//}

void Register::catchEvents(Event event, player& newPlayer) {
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
				handleMouseClick({ event.mouseButton.x, event.mouseButton.y }, newPlayer);
			}
			break;

		default:
			break;
		}
	}
}

void Register::handleKeyReleased(sf::Keyboard::Key keyCode, player& newPlayer) {
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

void Register::handleBackspace() {
	// Erase the last character if the string is not empty
	if (enterName) {
		if (!usernameRegister.isEmpty()) {
			usernameRegister.erase(usernameRegister.getSize() - 1);
		}
	}
	else {
		if (!passwordRegister.isEmpty()) {
			passwordRegister.erase(passwordRegister.getSize() - 1);
		}
	}
	changingOptionSound.play();
	updateInputFields();
}

void Register::handleEnter(player& newPlayer) {
	if (!usernameRegister.isEmpty()) {
		if (enterName) {
			enterName = false;  // Chuyển sang nhập mật khẩu
		}
		else {
			if (!isValidInput(passwordRegister) || !isValidInput(usernameRegister)) {
				errorMessage.setString("Invalid username or password! No spaces allowed.");
				return;  // Dừng nếu password không hợp lệ
			}
			newPlayer.username = std::string(usernameRegister);
			newPlayer.password = std::string(passwordRegister);

			if (checkCredentials(usernameRegister)) {
				setErrorMessage("Register successful!.");
				this->hide();
			}
			else {
				setErrorMessage("Username does exist!.");
			}
			resetFields();
		}
	}
	updateInputFields();
	changingOptionSound.play();
}

void Register::handleTextEntered(sf::Uint32 unicode) {
	if (unicode == '\b') return;  // Bỏ qua Backspace (đã xử lý riêng)

	if (unicode >= 32 && unicode <= 126) {  // Ký tự có thể in được
		if (enterName) {
			usernameRegister += static_cast<char>(unicode);
		}
		else {
			passwordRegister += static_cast<char>(unicode);
		}
	}
	updateInputFields();
}

bool Register::isValidInput(const sf::String& input) const {
	// Kiểm tra nếu chuỗi chứa bất kỳ khoảng trắng nào
	for (size_t i = 0; i < input.getSize(); ++i) {
		if (std::isspace(input[i])) {
			return false;
		}
	}
	return !input.isEmpty();  // Đảm bảo chuỗi không rỗng
}

void Register::resetFields() {
	usernameRegister = "";
	passwordRegister = "";
	enterName = true;  // Quay lại nhập tên người dùng
	updateInputFields();
}


void Register::updateInputFields() {
	inputFieldName.setString(usernameRegister + (enterName ? "_" : ""));
	inputFieldPassword.setString(std::string(passwordRegister.getSize(), '*'));
}

bool Register::checkCredentials(const sf::String& username) {
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
			if (username == storedUsername) {
				setErrorMessage("Username does exist!.");
				return false;  // username đã tồn tại
			}
		}
	}
	return true;  // đăng kí thành công
}

void Register::setErrorMessage(const sf::String& message) {
	errorMessage.setString(message);
}

void Register::handleMouseClick(sf::Vector2i mousePos, player& newPlayer) {
	if (display) {
		// Kiểm tra nếu nhấn nút Login
		if (loginButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			handleLogin(newPlayer);
		}

		// Kiểm tra nếu nhấn nút Register
		if (registerButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			handleRegister(newPlayer);
		}
	}
}

void Register::handleLogin(player& newPlayer) {
	this->hide();
	changingOptionSound.play();
}

void Register::handleRegister(player& newPlayer) {
	if (usernameRegister.getSize() < 6 || passwordRegister.getSize() < 6) {
		setErrorMessage("Username and password must be 6+ chars.");
		resetFields();
		return;
	}

	if (isValidInput(usernameRegister) && isValidInput(passwordRegister)) {
		// Ghi thông tin đăng ký vào file
		std::ofstream file(ACCOUNT_FILE, std::ios::app);
		if (!file.is_open()) {
			setErrorMessage("Error opening user file!");
			return;
		}

		file << usernameRegister.toAnsiString() << " " << passwordRegister.toAnsiString() << "\n";
		file.close();

		setErrorMessage("Registration successful! Please login.");
		resetFields();
	}
	else {
		setErrorMessage("Invalid username or password! No spaces allowed.");
	}
	changingOptionSound.play();
}
