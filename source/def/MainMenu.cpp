#include "../header/MainMenu.h"

MainMenu* MainMenu::instance = nullptr;

MainMenu::MainMenu()
{
    // Set initial values
    display = true;
    selectedOption = 0;
    newPlayer.lifes = 3;
    gameRunning = false;

    // Load fonts from file
    if (!menuFont.loadFromFile(MAIN_MENU_FONT))
    {
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

MainMenu* MainMenu::getInstance() {
    if (instance == nullptr) {
        instance = new MainMenu();
    }
    return instance;
}

void MainMenu::handleAllEvents(Event event)
{
    this->catchEvents(event);
    playerOptions.catchEvents(event, newPlayer);
    howToPlay.catchEvents(event);
    highScore.catchEvents(event);
    credits.catchEvents(event);
    options.catchEvents(event, newPlayer);
}

void MainMenu::catchEvents(Event event)
{
    // updateMenuOptionsColors();
    if (display)
    {
        if (event.type == Event::KeyReleased)
        {
            if (event.key.code == Keyboard::Up)
            {
                this->moveUp();
                changingOptionSound.play();
            }
            else if (event.key.code == Keyboard::Down)
            {
                this->moveDown();
                changingOptionSound.play();
            }
            else if (event.key.code == Keyboard::Enter)
            {
                this->hide();
                mainMenuHandleSelection();
                changingOptionSound.play();
            }
        }
    }
    updateMenuOptionsColors();
}

void MainMenu::drawAll(RenderWindow& window)
{
    this->draw(window);
    playerOptions.draw(window);
    howToPlay.draw(window);
    highScore.draw(window);
    credits.draw(window);
    options.draw(window);
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
    gameRunning = playerOptions.levelsList.gameEngine.gameRunning;
    // Nếu tất cả menu con đóng và không trong trạng thái game, hiển thị lại menu chính
    if (!playerOptions.display && !playerOptions.levelsList.display && !playerOptions.levelsList.level1.finished && !playerOptions.levelsList.level2.finished && !highScore.display && !playerOptions.levelsList.gameEngine.gameRunning)
    {
        show();
    }
}

void MainMenu::moveDown()
{
    // Di chuyển xuống, quay lại đầu nếu đến cuối
    selectedOption = (selectedOption + 1) % 6;
    // updateMenuOptionsColors();
}

void MainMenu::moveUp()
{
    // Di chuyển lên, quay lại cuối nếu ở đầu
    selectedOption = (selectedOption - 1 + 6) % 6;
    // updateMenuOptionsColors();
}

void MainMenu::mainMenuHandleSelection()
{
    switch (selectedOption)
    {
    case 0:
        playerOptions.show();
        controlEnemiesSpeed();
        break;
    case 1:
        howToPlay.show();
        break;
    case 2:
        highScore.show();
        break;
    case 3:
        credits.show();
        break;
    case 4:
        options.show();
        break;
    case 5:
        confirmExit();
        break;
    }
}

void MainMenu::controlMusic() {
	if (gameRunning) {
		if (options.levelSound.getStatus() == options.levelSound.Stopped)
			options.levelSound.play();

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

void MainMenu::confirmExit() // chưa có đẹp, nữa chỉnh lại dùm tao
{
    // Tạo cửa sổ mới cho hộp thoại xác nhận thoát
    sf::RenderWindow confirmWindow(sf::VideoMode(500, 300), "Confirm Exit");

    // Tải font chỉ một lần trong constructor hoặc khởi tạo trước
    static sf::Font font;
    if (!font.loadFromFile(GAME_FONT))
    {
        std::cerr << "Error loading font\n";
    }

    // Tạo văn bản hiển thị thông báo
    sf::Text text("Are you sure you want to exit? (Y/N)", font, 20);
    text.setFillColor(sf::Color::Black);
    text.setPosition((500 - text.getGlobalBounds().width) / 2, 50); // Căn giữa văn bản theo chiều ngang

    // Tạo các nút Yes và No
    sf::RectangleShape yesButton(sf::Vector2f(120, 50));
    yesButton.setPosition((500 - 120) / 2 - 140, 150); // Căn trái cho nút Yes
    yesButton.setFillColor(sf::Color::Green);

    sf::RectangleShape noButton(sf::Vector2f(120, 50));
    noButton.setPosition((500 - 120) / 2 + 20, 150); // Căn phải cho nút No
    noButton.setFillColor(sf::Color::Red);

    sf::Text yesText("Yes", font, 20);
    yesText.setPosition(yesButton.getPosition().x + (yesButton.getSize().x - yesText.getGlobalBounds().width) / 2,
        yesButton.getPosition().y + (yesButton.getSize().y - yesText.getGlobalBounds().height) / 2);
    yesText.setFillColor(sf::Color::White);

    sf::Text noText("No", font, 20);
    noText.setPosition(noButton.getPosition().x + (noButton.getSize().x - noText.getGlobalBounds().width) / 2,
        noButton.getPosition().y + (noButton.getSize().y - noText.getGlobalBounds().height) / 2);
    noText.setFillColor(sf::Color::White);

    // Vòng lặp xử lý sự kiện cho cửa sổ xác nhận
    while (confirmWindow.isOpen())
    {
        sf::Event event;
        while (confirmWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                confirmWindow.close(); // Đóng cửa sổ nếu ESC được nhấn
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(confirmWindow);

                // Kiểm tra xem người dùng có nhấn vào nút Yes
                if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    exit(0); // Thoát game
                }

                // Kiểm tra xem người dùng có nhấn vào nút No
                if (noButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    confirmWindow.close(); // Đóng cửa sổ xác nhận
                }
            }
        }

        // Vẽ UI
        confirmWindow.clear(sf::Color::White);
        confirmWindow.draw(text);
        confirmWindow.draw(yesButton);
        confirmWindow.draw(noButton);
        confirmWindow.draw(yesText);
        confirmWindow.draw(noText);
        confirmWindow.display();
    }
}
