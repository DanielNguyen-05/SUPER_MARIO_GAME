#include "../header/LevelsList.h"

LevelsList::LevelsList() : level1(gameEngine), level2(gameEngine), level3(gameEngine)
{
	// Set intial values
	display = false;
	selectedLevel = 0;
	maxLevel = 1;

	// Set Back Text Properties
	setBackText();
	setChangeOptionSound();

	// Load background
	if (!backGroundTexture.loadFromFile(LEVELS_LIST_BACKGROUND))
	{
		std::cout << "Can't load LEVELS_LIST_BACKGROUND\n";
	}
	backGroundSprite.setTexture(backGroundTexture);

	// Set OptionShadow Properties
	if (!optionShadowTexture.loadFromFile(MENU_SHADOW))
	{
		std::cout << "Can't load MENU_SHADOW\n";
	}
	optionShadowSprite.setTexture(optionShadowTexture);
	optionShadowSprite.setColor(Color(200, 0, 0, 80));
	optionShadowSprite.setPosition(695, 350 + selectedLevel * 120);
	optionShadowSprite.setScale(0.6, 1);

	// Set levels Name Text Properties
	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		levelsNameText[i].setFont(font);
		levelsNameText[i].setCharacterSize(50);
		levelsNameText[i].setString("Level " + to_string(i + 1));
		levelsNameText[i].setPosition(720, 350 + i * 120);
	}
}

void LevelsList::show(player newPlayer)
{
	checkOpendLevels();
	display = true;
	gameEngine.currentPlayer = newPlayer;

	selectedLevel = 0;
	optionShadowSprite.setPosition(695, 350 + selectedLevel * 120);

	// Find the last level this player has finished
}

void LevelsList::draw(RenderWindow& window)
{
	View defaultView(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	window.setView(defaultView);
	// checkShow(gameEngine.currentPlayer);
	// cout << level1.finished;
	if (display || level1.finished || level2.finished)
	{
		window.draw(backGroundSprite);
		window.draw(optionShadowSprite);
		window.draw(backText);
		for (int i = 0; i < NUMBER_OF_LEVELS; i++)
		{
			window.draw(levelsNameText[i]);
		}
	}
	else
	{
		level1.draw(window);
		level2.draw(window);
		level3.draw(window);
	}
}

void LevelsList::catchEvents(Event event, player& newPlayer)
{
	if (display || level1.finished || level2.finished)
	{
		switch (event.type)
		{
		case Event::KeyPressed:
			switch (event.key.code)
			{
			case Keyboard::Up:
				this->moveUp();
				changingOptionSound.play();
				break;
			case Keyboard::Down:
				this->moveDown();
				changingOptionSound.play();
				break;
			case Keyboard::Enter:
				this->hide();
				std::cout << "t3";
				gameEngine.gameRunning = true;
				switch (selectedLevel)
				{
				case 0:
					level1.finished = false;
					level2.finished = false;
					level1.start();
					break;
				case 1:
					level1.finished = false;
					level2.finished = false;
					level2.start();
					break;
				case 2:
					level3.start();
					break;
				}
				break;
			}
			break;
		case Event::KeyReleased:
			switch(event.key.code){
				case Keyboard::Escape:
				level1.finished = false;
				level2.finished = false;
				this->hide();
				newPlayer.username = "";
				changingOptionSound.play();
				break;
				}
			break;	
		}
	}
	level1.catchEvents(event);
	level2.catchEvents(event);
	level3.catchEvents(event);
}

void LevelsList::checkOpendLevels()
{
	int lines = getNumberOfLines();
	player tempPlayer;
	maxLevel = 1; // Default to level 1

	// Mở file
	playersFile.open(ACCOUNT_FILE);
	if (!playersFile.is_open())
	{
		cerr << "Error: Unable to open file " << ACCOUNT_FILE << endl;
		return;
	}

	// Đọc thông tin người chơi từ file
	for (int i = 0; i < lines; i++)
	{
		playersFile >> tempPlayer.username >> tempPlayer.level1Score >> tempPlayer.level2Score >> tempPlayer.level3Score;
		if (stoi(tempPlayer.level2Score) != -1)
			maxLevel = 2;
		if (stoi(tempPlayer.level3Score) != -1)
			maxLevel = 3;
	}

	// Đóng file
	playersFile.close();

	// Cập nhật các level đã mở
	setOpendLevels();
}

int LevelsList::getNumberOfLines()
{
	// Open the file to read
	playersFile.open(ACCOUNT_FILE);

	// Count how many lines in the file
	int cnt = 0;
	string temp;
	while (getline(playersFile, temp))
		cnt++;

	playersFile.close();
	playersFile.clear();

	return cnt;
}

void LevelsList::setOpendLevels()
{
	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		levelsNameText[i].setFillColor(Color::White);
		if (i >= maxLevel)
			levelsNameText[i].setFillColor(sf::Color(80, 80, 80));
	}
}

void LevelsList::moveUp() {
	if (selectedLevel >= maxLevel) return;
	selectedLevel = (selectedLevel == maxLevel - 1) ? 0 : selectedLevel + 1;
	updateShadowPosition();
}

void LevelsList::moveDown() {
	if (selectedLevel >= maxLevel) return;
	selectedLevel = (selectedLevel == 0) ? maxLevel - 1 : selectedLevel - 1;
	updateShadowPosition();
}

void LevelsList::updateShadowPosition() {
	optionShadowSprite.setPosition(695, 350 + selectedLevel * 120);
}