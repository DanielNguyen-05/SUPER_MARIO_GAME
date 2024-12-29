#include "../header/CharacterOptionsMenu.h"
#include "../header/MainMenu.h"

CharacterOptionsMenu::CharacterOptionsMenu()
{
    display = false;

    // Load fonts from file
    if (!font.loadFromFile(MAIN_MENU_FONT))
    {
        cout << "Can't load MAIN_MENU_FONT\n";
    }

    newUser = false;

    selectedCharacterOption = 0;

    // Set Back Text Properties
    setBackText();
    setChangeOptionSound();

    if (!backGroundTexture.loadFromFile(PLAYER_NAME_BACKGROUND))
    {
        std::cout << "Can't load PLAYER_NAME_BACKGROUND\n";
    }
    backGroundSprite.setTexture(backGroundTexture);

    // Cấu hình tiêu đề
    titleText.setFont(font);
    titleText.setString("Select Character");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Red);
    titleText.setPosition(800 - titleText.getGlobalBounds().width / 2.f, 200);

    // Cấu hình các tùy chọn menu
    std::vector<std::string> options = {"Mario", "Luigi"};
    float startY = 400.0f;
    for (size_t i = 0; i < options.size(); ++i)
    {
        characterOptions[i].setFont(font);
        characterOptions[i].setString(options[i]);
        characterOptions[i].setCharacterSize(50);
        characterOptions[i].setFillColor(sf::Color::White);
        characterOptions[i].setPosition(800 - characterOptions[i].getGlobalBounds().width / 2.f, startY);

        characterOptionsOutline[i].setFont(font);
        characterOptionsOutline[i].setFillColor(sf::Color::Black); // Màu viền
        characterOptionsOutline[i].setCharacterSize(50);
        characterOptionsOutline[i].setStyle(sf::Text::Regular);
        characterOptionsOutline[i].setString(options[i]);
        characterOptionsOutline[i].setPosition(800 - characterOptions[i].getGlobalBounds().width / 2.f - 2, startY - 2);
        startY += 80.0f;
    }
}

// Vẽ giao diện
void CharacterOptionsMenu::draw(sf::RenderWindow &window)
{
    if (display)
    {
        window.draw(backGroundSprite);
        window.draw(titleText);
        for (const auto &option : characterOptions)
            window.draw(option);

        window.draw(backText);
    }
}

void CharacterOptionsMenu::catchEvents(Event event)
{
    if (display)
    {
        switch (event.type)
        {
        case Event::KeyReleased:
            handleKeyReleased(event.key.code);
            break;
        default:
            break;
        }
    }
    updateCharacterOptionsColors();
}

void CharacterOptionsMenu::handleKeyReleased(sf::Keyboard::Key keyCode)
{
    if (!newUser)
    {
        newUser = true;
    }
    else
    {
        switch (keyCode)
        {
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
            handleEnter();
            break;
        case sf::Keyboard::Escape:
            this->hide();
            newUser = false;
            selectedCharacterOption = 0;
            changingOptionSound.play();
            break;
        default:
            break;
        }
    }
}

void CharacterOptionsMenu::handleEnter()
{
    switch (selectedCharacterOption)
    {
    case 0:
        MainMenu::getInstance()->setSelectedCharacterType(CharacterTypeEnum::MARIO);
        break;
    case 1:
        MainMenu::getInstance()->setSelectedCharacterType(CharacterTypeEnum::LUIGI);
        break;
    }
}

void CharacterOptionsMenu::moveDown()
{
    // Di chuyển xuống, quay lại đầu nếu đến cuối
    selectedCharacterOption = (selectedCharacterOption + 1) % 2;
}

void CharacterOptionsMenu::moveUp()
{
    // Di chuyển lên, quay lại cuối nếu ở đầu
    selectedCharacterOption = (selectedCharacterOption - 1 + 2) % 2;
}

// Hàm cập nhật màu sắc của các menu options
void CharacterOptionsMenu::updateCharacterOptionsColors()
{
    for (int i = 0; i < 2; i++)
    {
        if (i == selectedCharacterOption)
        {
            characterOptions[i].setFillColor(sf::Color::Yellow);     // Màu nổi bật
            characterOptionsOutline[i].setFillColor(sf::Color::Red); // Viền nổi bật
        }
        else
        {
            characterOptions[i].setFillColor(sf::Color::White);        // Màu bình thường
            characterOptionsOutline[i].setFillColor(sf::Color::Black); // Viền bình thường
        }
    }
}