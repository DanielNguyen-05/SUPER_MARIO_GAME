#include "../header/PlayerOptionsMenu.h"

PlayerOptionsMenu::PlayerOptionsMenu() : user(), levelsList(){
    display = false;

    // Load fonts from file
    if (!font.loadFromFile(MAIN_MENU_FONT)) {
        cout << "Can't load MAIN_MENU_FONT\n";
    }

    newUser = false;
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
    titleText.setFillColor(sf::Color::Red);
    titleText.setPosition(800 - titleText.getGlobalBounds().width / 2.f, 200);

    // Cấu hình các tùy chọn menu
    std::vector<std::string> options = {"New Game", "Continue"};
    float startY = 400.0f;
    for (size_t i = 0; i < options.size(); ++i) {
        PlayerOptions[i].setFont(font);
        PlayerOptions[i].setString(options[i]);
        PlayerOptions[i].setCharacterSize(50);
        PlayerOptions[i].setFillColor(sf::Color::White);
        PlayerOptions[i].setPosition(800 - PlayerOptions[i].getGlobalBounds().width / 2.f, startY);

        PlayerOptionsOutline[i].setFont(font);
        PlayerOptionsOutline[i].setFillColor(sf::Color::Black); // Màu viền
        PlayerOptionsOutline[i].setCharacterSize(50);
        PlayerOptionsOutline[i].setStyle(sf::Text::Regular);
        PlayerOptionsOutline[i].setString(options[i]);
        PlayerOptionsOutline[i].setPosition(800 - PlayerOptions[i].getGlobalBounds().width / 2.f - 2, startY - 2);
        startY += 80.0f;
    }
}


// Vẽ giao diện
void PlayerOptionsMenu::draw(sf::RenderWindow& window) {
	if (display) {
        window.draw(backGroundSprite);
        window.draw(titleText);
        for (const auto& option : PlayerOptions)
            window.draw(option);
        
        window.draw(backText);
    }
    user.draw(window);
    levelsList.draw(window);
}


void PlayerOptionsMenu::catchEvents(Event event, player& newPlayer) {
   if (display) {
		switch (event.type) {
		case Event::KeyReleased:
			handleKeyReleased(event.key.code, newPlayer);
			break;

		/*case Event::MouseButtonReleased:
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 2; ++i) {
                if (isHovering(PlayerOptions[i], mousePos)) {
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
    updatePlayerOptionsColors();
    user.catchEvents(event, newPlayer, levelsList);
    levelsList.catchEvents(event, newPlayer);
}

void PlayerOptionsMenu::handleKeyReleased(sf::Keyboard::Key keyCode, player& newPlayer) {
    if (!newUser){
        newUser = true;
    }
    else
    {
        switch (keyCode) {
            case sf::Keyboard::Up:
                this->moveUp();
                changingOptionSound.play();
                break;
            case sf::Keyboard::Down:
                this->moveDown();
                changingOptionSound.play();
                break;

            case sf::Keyboard::Enter:
                this->hide();
                newUser = false;
                handleEnter(newPlayer);
                break;

            case sf::Keyboard::Escape:
                this->hide();
                selectedPlayerOption = 0;
                newUser = false;
                changingOptionSound.play();
                break;

            default:
                break;
        }
    }
}

void PlayerOptionsMenu::handleEnter(player& newPlayer){
    switch (selectedPlayerOption)
    {
    case 0:
        user.show(newPlayer);
       // controlEnemiesSpeed();
        break;
    case 1:
        levelsList.show(newPlayer);
        selectedPlayerOption = 0;
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

// Hàm cập nhật màu sắc của các menu options
void PlayerOptionsMenu::updatePlayerOptionsColors()
{
    for (int i = 0; i < 2; i++)
    {
        if (i == selectedPlayerOption)
        {
            PlayerOptions[i].setFillColor(sf::Color::Yellow);     // Màu nổi bật
            PlayerOptionsOutline[i].setFillColor(sf::Color::Red); // Viền nổi bật
        }
        else
        {
            PlayerOptions[i].setFillColor(sf::Color::White);        // Màu bình thường
            PlayerOptionsOutline[i].setFillColor(sf::Color::Black); // Viền bình thường
        }
    }
}

bool PlayerOptionsMenu::isHovering(const sf::Text& text, const sf::Vector2i& mousePos) {
    return text.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}




