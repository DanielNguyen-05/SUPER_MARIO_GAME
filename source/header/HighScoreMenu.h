#pragma once
#include "Menu.h"

class HighScoreMenu : public Menu
{
private:
	/***			Properties				***/
	position highScoresPos;
	Text highScoreText[3][2];
	vector<pair<int, pair<int, string>>> players;
	fstream playersFile;

public:
	// Constructor
	HighScoreMenu();

	// Draw Menu contents
	void draw(RenderWindow &window) override;

	// Make Menu display
	void show() override;

	// Fill High score board with the top 10
	void fillHighScore();

	// Sort players info according to score
	void sortPlayersFile();

	// Make a vector contain players information collected form file
	void arrangePlayersInfo();

	// Count how many lines in specific file
	int getNumberOfLines();
};
