#include "../header/MainMenu.h"

MainMenu::MainMenu() {
    // Set initial values
    this->show();
    selectedOption = 0;
    newPlayer.lifes = 3;
    gameRunning = false;

    // Load fonts from file
    if (!menuFont.loadFromFile(MAIN_MENU_FONT)) {
        cout << "Can't load MAIN_MENU_FONT\n";
    }

    // Load backgrounds
    if (!backGroundTexture.loadFromFile(MAIN_MENU_BACKGROUND))
    {
        cout << "Can't load MAIN_MENU_BACKGROUND\n";
    }
    backGroundSprite.setTexture(backGroundTexture);

    setChangeOptionSound();

    // Helper variables
    float width = 1000;
    float hight = 200;
    string OptionsTemp[6] = {
        "   START",
        "  TUTORIAL",
        " LEADERBOARD", // Top 3 players
        "   CREDITS",   // Introduce the team
        "   OPTIONS",   // Music control
        "    EXIT" };

    for (int i = 0; i < 6; i++)
    {
        // Main text
        menuOptions[i].setFont(menuFont);
        menuOptions[i].setFillColor(sf::Color::White);
        menuOptions[i].setCharacterSize(43);
        menuOptions[i].setStyle(sf::Text::Regular);
        menuOptions[i].setString(OptionsTemp[i]);

        // Outline text
        menuOptionsOutline[i].setFont(menuFont);
        menuOptionsOutline[i].setFillColor(sf::Color::Black); // Màu viền
        menuOptionsOutline[i].setCharacterSize(43);
        menuOptionsOutline[i].setStyle(sf::Text::Regular);
        menuOptionsOutline[i].setString(OptionsTemp[i]);

        // Position
        hight += 70;
        menuOptions[i].setPosition(width, hight);
        menuOptionsOutline[i].setPosition(width - 2, hight - 2); // Dịch viền một chút
    }
}

void MainMenu::handleAllEvents(Event event)
{
    this->catchEvents(event);
    playerName.catchEvents(event, newPlayer);
    highScore.catchEvents(event);
}

void MainMenu::catchEvents(Event event)
{
    if (display)
    {
        if (event.type == Event::KeyReleased)
        {
            if (event.key.code == Keyboard::Up || event.key.code == Keyboard::A)
            {
                this->moveUp();
                changingOptionSound.play();
            }
            else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
            {
                this->moveDown();
                changingOptionSound.play();
            }
            else if (event.key.code == Keyboard::Enter)
            {
                mainMenuHandleSelection();
                changingOptionSound.play();
            }
        }
    }
}

void MainMenu::drawAll(RenderWindow& window)
{
    this->draw(window);
    playerName.draw(window);
    highScore.draw(window);
}

void MainMenu::draw(RenderWindow& window)
{
    checkShow();
    controlMusic();
    if (display)
    {
        window.draw(backGroundSprite);

        for (int i = 0; i < 6; i++)
        {
            window.draw(menuOptionsOutline[i]); // Vẽ viền chữ
            window.draw(menuOptions[i]);        // Vẽ chữ chính
        }
    }
}

void MainMenu::checkShow()
{
    // Nếu tất cả menu con đóng và không trong trạng thái game, hiển thị lại menu chính
    if (!playerName.display && !highScore.display && !gameRunning)
    {
        show();
    }
}

void MainMenu::moveDown()
{
    // Di chuyển xuống, quay lại đầu nếu đến cuối
    selectedOption = (selectedOption + 1) % 6;
    updateMenuOptionsColors();
}

void MainMenu::moveUp()
{
    // Di chuyển lên, quay lại cuối nếu ở đầu
    selectedOption = (selectedOption - 1 + 6) % 6;
    updateMenuOptionsColors();
}

void MainMenu::mainMenuHandleSelection()
{
    // Thực hiện hành động tương ứng với lựa chọn hiện tại
    this->hide();
    switch (selectedOption)
    {
    case 0:
        playerName.show();
        controlEnemiesSpeed();
        break;
    case 1:
        // howToPlay.show();
        break;
    case 2:
        highScore.show();
        break;
    case 3:
        // credits.show();
        break;
    case 4:
        options.show();
        break;
    case 5:
        exit(0);
        break;
    }
}

void MainMenu::controlMusic()
{
    // Nếu đang chạy game, kiểm soát âm nhạc
    if (gameRunning) {
        if (options.menuSound.getStatus() == options.menuSound.Playing)
            options.menuSound.stop();
    }
}

void MainMenu::controlEnemiesSpeed()
{
    switch (newPlayer.lifes)
    {
    case 5:
        newPlayer.enemiesSpeed = 2;
        break;
    case 3:
        newPlayer.enemiesSpeed = 3;
        break;
    case 1:
        newPlayer.enemiesSpeed = 7;
        break;
    default:
        newPlayer.enemiesSpeed = 1;
        break;
    }
}

// Hàm cập nhật màu sắc của các menu options
void MainMenu::updateMenuOptionsColors()
{
    for (int i = 0; i < 6; i++)
    {
        if (i == selectedOption)
        {
            menuOptions[i].setFillColor(sf::Color::Yellow);     // Màu nổi bật
            menuOptionsOutline[i].setFillColor(sf::Color::Red); // Viền nổi bật
        }
        else
        {
            menuOptions[i].setFillColor(sf::Color::White);        // Màu bình thường
            menuOptionsOutline[i].setFillColor(sf::Color::Black); // Viền bình thường
        }
    }
}
