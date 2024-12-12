#include "../header/PlayerOptionsMenu.h"

PlayerOptionsMenu::PlayerOptionsMenu() {
    display = false;
    if (!font.loadFromFile(MAIN_MENU_FONT)) {
        std::cerr << "Error loading font!" << std::endl;
    }

    selectedPlayerOption = 0;

    // Set Back Text Properties
	setBackText();
	setChangeOptionSound();

    if (!backGroundTexture.loadFromFile(PLAYER_NAME_BACKGROUND)) { std::cout << "Can't load PLAYER_NAME_BACKGROUND\n"; }
	backGroundSprite.setTexture(backGroundTexture);
    // Cấu hình tiêu đề
    titleText.setFont(font);
    titleText.setString("Super Mario Game");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(800 - titleText.getGlobalBounds().width / 2.f, 380);

    // Cấu hình các tùy chọn menu
    std::vector<std::string> options = {"New Game", "Continue"};
    float startY = 450.0f;
    for (size_t i = 0; i < options.size(); ++i) {
        Options[i].setFont(font);
        Options[i].setString(options[i]);
        Options[i].setCharacterSize(30);
        Options[i].setFillColor(sf::Color::White);
        Options[i].setPosition(800 - Options[i].getGlobalBounds().width / 2.f, startY);
        startY += 50.0f;
    }
}


// Vẽ giao diện
void PlayerOptionsMenu::draw(sf::RenderWindow& window) {
	if (display) {
        window.draw(backGroundSprite);
        window.draw(titleText);
        for (const auto& option : Options)
            window.draw(option);
        
        window.draw(backText);
    }
    user.draw(window);
}


void PlayerOptionsMenu::catchEvents(Event event, player& newPlayer) {
   if (display) {
		switch (event.type) {
		case Event::KeyPressed:
			handleKeyPressed(event.key.code, newPlayer);
			break;

		/*case Event::MouseButtonReleased:
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 2; ++i) {
                if (isHovering(Options[i], mousePos)) {
                    if (i == 0) {
                        std::cout << "New Game clicked" << std::endl;
                        // Thêm logic xử lý cho New Game
                        } else if (i == 1) {
                            std::cout << "Continue clicked" << std::endl;
                            // Thêm logic xử lý cho Continue
                        }
                    }
            }
			}
			break;*/
		}
	}
    user.catchEvents(event, newPlayer);
}

void PlayerOptionsMenu::handleKeyPressed(sf::Keyboard::Key keyCode, player& newPlayer) {
	switch (keyCode) {
        case sf::Keyboard::Up:
            this->moveUp();
                changingOptionSound.play();
        case sf::Keyboard::Down:
            this->moveDown();
                changingOptionSound.play();

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

void PlayerOptionsMenu::handleEnter(player& newPlayer){
    switch (selectedPlayerOption)
    {
    case 0:
        this->hide();
        user.show(newPlayer);
        //levelsList.draw(window);
       // controlEnemiesSpeed();
        break;
    case 1:
    //levelsList.draw(window);
    //controlEnemiesSpeed();
    break;
    }     
}


void PlayerOptionsMenu::moveDown()
{
    // Di chuyển xuống, quay lại đầu nếu đến cuối
    selectedPlayerOption = (selectedPlayerOption + 1) % 2;
    // updateMenuOptionsColors();
}

void PlayerOptionsMenu::moveUp()
{
    // Di chuyển lên, quay lại cuối nếu ở đầu
    selectedPlayerOption = (selectedPlayerOption - 1 + 2) % 2;
    // updateMenuOptionsColors();
}
bool PlayerOptionsMenu::isHovering(const sf::Text& text, const sf::Vector2i& mousePos) {
    return text.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}




