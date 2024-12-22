#include "../header/HighScoreMenu.h"
#include "../header/HighScoreMenu.h"

// Constructor
HighScoreMenu::HighScoreMenu()
{
    display = false;

    // Load font
    if (!font.loadFromFile(CAIRO_REGULAR))
    {
        std::cout << "Failed to load font" << std::endl;
    }

    // Load background
    if (!backGroundTexture.loadFromFile(HIGH_SCORE_BACKGROUND))
    {
        std::cout << "Failed to load HighScore background texture" << std::endl;
    }
    backGroundSprite.setTexture(backGroundTexture);

    // Set vị trí của các thành phần high score
    highScoresPos.x = 518;
    highScoresPos.y = 450;

    // Set các thành phần text high score
    for (int i = 0; i < 3; i++)
    {
        highScoreText[i][0].setFont(font); // Tên người chơi
        highScoreText[i][1].setFont(font); // Điểm số

        highScoreText[i][0].setFillColor(sf::Color::Green);
        highScoreText[i][1].setFillColor(sf::Color::White);

        highScoreText[i][0].setCharacterSize(32);
        highScoreText[i][1].setCharacterSize(32);
    }
    // Vị trí text tên và điểm tương ứng
    highScoreText[1][0].setPosition(highScoresPos.x, highScoresPos.y);
    highScoreText[1][1].setPosition(highScoresPos.x, highScoresPos.y + 50);

    // Khoảng cách giữa các dòng
    highScoresPos.x += 225;

    // Vị trí text tên và điểm tương ứng
    highScoreText[0][0].setPosition(highScoresPos.x, highScoresPos.y - 125);
    highScoreText[0][1].setPosition(highScoresPos.x, highScoresPos.y - 75);

    // Khoảng cách giữa các dòng
    highScoresPos.x += 300;

    // Vị trí text tên và điểm tương ứng
    highScoreText[2][0].setPosition(highScoresPos.x, highScoresPos.y);
    highScoreText[2][1].setPosition(highScoresPos.x, highScoresPos.y + 50);

    // Khoảng cách giữa các dòng
    highScoresPos.x += 300;
}

// Hàm vẽ
void HighScoreMenu::draw(RenderWindow &window)
{
    if (display)
    {
        // Vẽ nền
        window.draw(backGroundSprite);

        /*// Vẽ các biểu tượng thứ hạng
        for (int i = 0; i < 3; i++) {
            window.draw(rankSprites[i]);
        }
*/
        // Vẽ thông tin xếp hạng (tên + điểm)
        for (int i = 0; i < 3; i++)
        {
            window.draw(highScoreText[i][0]);
            window.draw(highScoreText[i][1]);
        }
    }
}

// Hiển thị bảng xếp hạng
void HighScoreMenu::show()
{
    display = true;
    fillHighScore();
}

// Lấy dữ liệu từ file và hiển thị lên bảng xếp hạng
void HighScoreMenu::fillHighScore()
{
    // Sắp xếp thông tin từ file
    sortPlayersFile();

    // Gán thông tin top 3 người chơi vào text
    for (int i = 0; i < 3; i++)
    {
        highScoreText[i][0].setString(players[i].second.second);    // Tên người chơi
        highScoreText[i][1].setString(to_string(players[i].first)); // Điểm
    }
}

// Sắp xếp thông tin người chơi theo điểm
void HighScoreMenu::sortPlayersFile()
{
    // Làm trống danh sách hiện tại
    players.clear();

    // Lấy thông tin từ file
    arrangePlayersInfo();

    // Sắp xếp danh sách theo thứ tự giảm dần
    sort(players.rbegin(), players.rend());
}

// Thu thập thông tin từ file và lưu vào vector
void HighScoreMenu::arrangePlayersInfo()
{
    int lines = getNumberOfLines(); // Số dòng trong file
    player tempPlayer;

    playersFile.open(PLAYERS_FILE);

    // Đọc dữ liệu từ file
    for (int i = 0; i < lines; i++)
    {
        playersFile >> tempPlayer.username >> tempPlayer.level1Score >> tempPlayer.level2Score >> tempPlayer.level3Score;
        if (tempPlayer.level2Score != "-1")
            tempPlayer.level = "2";
        if (tempPlayer.level3Score != "-1")
            tempPlayer.level = "3";
        int totalScore = atoi(tempPlayer.level1Score.c_str()) +
                         atoi(tempPlayer.level2Score.c_str()) +
                         atoi(tempPlayer.level3Score.c_str());
        players.push_back({totalScore, {stoi(tempPlayer.level), tempPlayer.username}});
    }
    playersFile.close();
    playersFile.clear();
}

// Đếm số dòng trong file
int HighScoreMenu::getNumberOfLines()
{
    playersFile.open(PLAYERS_FILE);

    int cnt = 0;
    string temp;
    while (getline(playersFile, temp))
        cnt++;

    playersFile.close();
    playersFile.clear();

    return cnt;
}
