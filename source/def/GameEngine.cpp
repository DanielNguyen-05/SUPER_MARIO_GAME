#include "../header/GameEngine.h"

GameEngine::GameEngine() : winner(), gameover(), CHAR_TYPE(CharacterTypeEnum::MARIO)
{
	// Set initial values
	levelTime = 300;
	scoreInt = coinsInt = currentTime = counterTime = 0;
	remainTime = -1;
	scoreStr << "SCORE\n000000";
	coinsStr << "x00";
	fontSize = 40;
	lifeScreen = gameRunning = gameOverScreen = WinnerScreen = false;
	currentPlayer.lifes = 3;

	character = CharacterFactory::createCharacter(CHAR_TYPE);

	// Load font from file
	if (!headerFont.loadFromFile(GAME_HEADER_FONT))
	{
		std::cout << "Can't load GAME_HEADER_FONT\n";
	}
	floatingTextFont.loadFromFile(FLOATING_FONT);

	// set Score Text properties
	scoreText.setPosition(20, 20);
	scoreText.setFont(headerFont);
	scoreText.setCharacterSize(fontSize);
	scoreText.setString(scoreStr.str());

	// set Timer Text Properties
	timerText.setPosition(1400, 5);
	timerText.setFont(headerFont);
	timerText.setCharacterSize(fontSize);

	// Set Coins Text Properties
	coinsText.setPosition(700, 5);
	coinsText.setFont(headerFont);
	coinsText.setCharacterSize(fontSize);
	coinsText.setString(coinsStr.str());

	// Set Coin Sprite Properties
	coinRect = IntRect(0, 86, 33, 30);
	coinTexture.loadFromFile(ITEMS);
	coinSprite.setTexture(coinTexture);
	coinSprite.setTextureRect(coinRect);
	coinSprite.setPosition(675, 38);
	coinSprite.setScale(1.5, 1.5);
	coinSprite.setOrigin(coinRect.width / 2, coinRect.height / 2);

	// Set Level name Text Properties
	// levelText.setPosition(1000, 5);
	// levelText.setFont(headerFont);
	// levelText.setCharacterSize(fontSize);
	// levelText.setStyle(Text::Bold);

	// Set levels Map values
	levelsMap["level 1"] = 1;
	levelsMap["level 2"] = 2;
	levelsMap["level 3"] = 3;

	// Set Lifes Text Properties
	lifeText.setCharacterSize(50);
	lifeText.setFont(headerFont);
	lifeText.setPosition(820, 420);
	lifeStr << "x" << currentPlayer.lifes;
	lifeText.setString(lifeStr.str());

	// Set Mario Sprite Properties
	updateCharLifeSprite();

	// Load Game Sound Effects
	popUpBuffer.loadFromFile(POPUP_SOUND);
	popUpSound.setBuffer(popUpBuffer);

	smashBuffer.loadFromFile(SMASH_SOUND);
	smashSound.setBuffer(smashBuffer);

	coinBuffer.loadFromFile(COIN_SOUND);
	coinSound.setBuffer(coinBuffer);

	powerUpBuffer.loadFromFile(POWERUP_SOUND);
	powerUpSound.setBuffer(powerUpBuffer);

	killBuffer.loadFromFile(KILL_SOUND);
	killSound.setBuffer(killBuffer);

	if (!powerUpAppearBuffer.loadFromFile(POWERUP_APPEAR_SOUND))
	{
		cout << "faild to load powerup appear\n";
	}
	powerUpAppearSound.setBuffer(powerUpAppearBuffer);

	// Load Game Textures
	questionTexture.loadFromFile(QUESTION_BLOCK);
	stoneTexture.loadFromFile(STONE_BLOCK);
	itemTexture.loadFromFile(ITEMS);
	enemyTextrue.loadFromFile(ENEMY);

	for (int i = 0; i < 6; i++)
	{
		smashTextures[i].loadFromFile(SMASH_STONE_BLOCK + to_string(i) + ".png");
	}

	// Tải texture cho bullet
	if (!bulletTexture.loadFromFile(MUSIC_BALL))
	{
		// Xử lý lỗi nếu không thể tải texture
		std::cerr << "Error loading bullet texture!" << std::endl;
	}
}

void GameEngine::updateCharLifeSprite()
{
	charLifeSprite.setTexture(character->charTexture);
	charLifeSprite.setTextureRect(IntRect(0, 96, 28, 32));
	charLifeSprite.setScale(2, 2);
	charLifeSprite.setOrigin(14, 16);
	charLifeSprite.setPosition(780, 450);
}

void GameEngine::updateScore(int IncScore)
{
	// Increase current score
	scoreInt += IncScore;
	// clear score_str
	scoreStr.str(string());
	scoreStr << "SCORE\n"
		<< setw(6) << setfill('0') << scoreInt;
	scoreText.setString(scoreStr.str());
}

void GameEngine::startCountDown()
{
	timer.restart();
}

void GameEngine::updateTimer()
{
	// clear timer_str
	timerStr.str(string());
	currentTime = timer.getElapsedTime().asSeconds();
	counterTime = levelTime - currentTime;

	if (counterTime >= 0)
	{
		timerStr << "TIME\n "
			<< setw(3) << setfill('0') << counterTime;
		timerText.setString(timerStr.str());
	}
	else
	{ /* Do Nothing */
	}

	if (counterTime == 0 && remainTime == -1) {
		gameOverScreen = true;
		character->startDie();
	}
}

void GameEngine::updateCoins()
{
	coinsInt++;
	coinsStr.str(string());
	coinsStr << "x" << setw(2) << setfill('0') << coinsInt;
	coinsText.setString(coinsStr.str());
}

bool GameEngine::isTimerFinished()
{
	if (counterTime == 0)
		return true;
	else
		return false;
}

void GameEngine::timeToScore()
{
	if (remainTime > 0)
	{
		if (convertTimer.getElapsedTime().asMilliseconds() >= 6)
		{
			remainTime--;
			levelTime = remainTime;

			updateTimer();
			updateScore(50);

			timer.restart();
			convertTimer.restart();
		}
	}
}

void GameEngine::startTimeToScore()
{
	remainTime = counterTime;
}

void GameEngine::draw(RenderWindow& window)
{
	coinAnimation();
	updateTimer();
	updateLifes();

	if (WinnerScreen)
	{
		cout << getScore();
		int total_score = stoi(currentPlayer.level1Score) + stoi(currentPlayer.level2Score) + getScore();
		View defaultView(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
		window.setView(defaultView);
		winner.draw(window, total_score, coinsInt);
	}
	if (gameOverScreen)
	{
		View defaultView(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
		window.setView(defaultView);
		gameover.draw(window, getScore(), coinsInt);
	}
	else
	{

		window.draw(scoreText);
		window.draw(timerText);
		window.draw(coinsText);
		// window.draw(levelText);
		window.draw(coinSprite);
		if (lifeScreen)
			startLifeScreen(window);
	}
}

void GameEngine::startLifeScreen(RenderWindow& window)
{
	Clock lifeScreenClock;
	while (lifeScreenClock.getElapsedTime().asSeconds() < 3)
	{
		window.clear();
		window.draw(scoreText);
		window.draw(timerText);
		window.draw(coinsText);
		// window.draw(levelText);
		window.draw(coinSprite);
		window.draw(lifeText);
		window.draw(charLifeSprite);
		window.display();
	}
	lifeScreen = false;
}

void GameEngine::setLevelName(string levelName)
{
	levelText.setString(levelName);
}

// level truyền vào là để biết coi nó nên cập nhật điểm của level nào (trường hợp nó chơi xong lv1 mà nó không chơi lv2, nó quay lại chơi lv1 để cải thiện điểm)
void GameEngine::addPlayerInfo(int level)
{
	int currentScore = scoreInt + currentTime * 25;
	cout << currentTime;
	std::ifstream inputFile(ACCOUNT_FILE);
	std::ostringstream tempBuffer;
	bool userFound = false;

	// Đọc toàn bộ file và xử lý từng dòng
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);
		std::string fileUsername;
		int level1Score, level2Score, level3Score;

		// Giả định file có cấu trúc: username level0Score level1Score level2Score
		if (iss >> fileUsername >> level1Score >> level2Score >> level3Score)
		{
			if (fileUsername == currentPlayer.username)
			{
				userFound = true;
				if (level == 1)
				{
					level1Score = currentScore;
					if (level2Score == -1)
						level2Score = 0;
				}
				else if (level == 2)
				{
					level2Score = currentScore;
					if (level3Score == -1)
						level3Score = 0;
				}
				else if (level == 3)
				{
					level3Score = currentScore;
				}

				// Ghi lại dòng đã cập nhật
				tempBuffer << fileUsername << ' ' << level1Score << ' ' << level2Score << ' ' << level3Score << '\n';
			}
			else
			{
				// Ghi lại dòng không liên quan
				tempBuffer << line << '\n';
			}
		}
		else
		{
			// Nếu dòng không đúng định dạng, giữ nguyên
			tempBuffer << line << '\n';
		}
	}
	inputFile.close();

	if (!userFound)
	{
		// Nếu không tìm thấy user, thêm mới
		tempBuffer << currentPlayer.username << " 0 -1 -1\n";
	}

	// Ghi nội dung đã cập nhật lại vào file
	std::ofstream outputFile(ACCOUNT_FILE);
	outputFile << tempBuffer.str();
	outputFile.close();
}

void GameEngine::coinAnimation()
{
	if (coinTimer.getElapsedTime().asSeconds() > 0.2f)
	{
		coinRect.left += 33;
		if (coinRect.left > 99)
			coinRect.left = 0;
		coinSprite.setTextureRect(coinRect);
		coinTimer.restart();
	}
}

void GameEngine::setHeaderPosition(position screenCenter)
{
	float topLeft = screenCenter.x - (WINDOW_WIDTH / 2);
	scoreText.setPosition(topLeft + 20, 20);   // Score
	timerText.setPosition(topLeft + 1400, 5);  // Timer
	coinsText.setPosition(topLeft + 700, 5);   // Coins Counter
	coinSprite.setPosition(topLeft + 675, 38); // Coin sprite
	// levelText.setPosition(topLeft + 1000, 5);  // Level Name
	lifeText.setPosition(topLeft + 820, 420);
	charLifeSprite.setPosition(topLeft + 780, 450);
}

void GameEngine::updateLifes()
{
	lifeStr.str(string());
	if (character->dead)
	{
		if (currentPlayer.lifes > 1)
		{
			currentPlayer.lifes--;
			lifeStr << "x" << currentPlayer.lifes;
			character->dead = false;
			lifeScreen = true;
		}
		else
		{
			lifeStr << "Game Over";
			gameOverScreen = true;
			// gameRunning = false;
			lifeScreen = false;
		}
	}

	lifeText.setString(lifeStr.str());
}

void GameEngine::reset()
{
	scoreInt = 0;
	coinsInt = 0;
	currentPlayer.lifes = 3;
	gameOverScreen = WinnerScreen = false;

	scoreStr.str(string());
	scoreStr << "SCORE\n"
		<< setw(6) << setfill('0') << scoreInt;
	scoreText.setString(scoreStr.str());

	scoreText.setPosition(20, 20);
	scoreText.setFont(headerFont);
	scoreText.setCharacterSize(fontSize);
	scoreText.setString(scoreStr.str());

	coinsStr.str(string());
	coinsStr << "x" << setw(2) << setfill('0') << coinsInt;
	coinsText.setString(coinsStr.str());

	// Set Coins Text Properties
	coinsText.setPosition(700, 5);
	coinsText.setFont(headerFont);
	coinsText.setCharacterSize(fontSize);
	coinsText.setString(coinsStr.str());

	// Set Coin Sprite Properties
	coinRect = IntRect(0, 86, 33, 30);
	coinTexture.loadFromFile(ITEMS);
	coinSprite.setTexture(coinTexture);
	coinSprite.setTextureRect(coinRect);
	coinSprite.setPosition(675, 38);
	coinSprite.setScale(1.5, 1.5);
	coinSprite.setOrigin(coinRect.width / 2, coinRect.height / 2);

	// set Timer Text Properties
	timerText.setPosition(1400, 5);
	timerText.setFont(headerFont);
	timerText.setCharacterSize(fontSize);
}