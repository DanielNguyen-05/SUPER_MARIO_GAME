#pragma once
#include "../header/DEFINITION.h"
#include "../header/Menu.h"
//#include "../Header/GameEngine.h"
//#include "../Header/Level1.h"
//#include "../Header/Level2.h"

#define NUMBER_OF_LEVELS 3

class LevelsList : public Menu
{
private:
	//Level1 level1;
	//Level2 level2;
    //Level3 level3;
	Text levelsNameText[NUMBER_OF_LEVELS];
	Texture optionShadowTexture;
	Sprite optionShadowSprite;
	int selectedLevel;
    int maxLevel;
	fstream playersFile;

public:
	//GameEngine gameEngine;

	// Constructor
	LevelsList();

	// Draw LevelList Menu
	void draw(RenderWindow& window) override;


	//Handle all event happend on Levels List window
	void catchEvents(Event event, player& newPlayer);


	// Make LevelList Menu display
	void show(player newPlayer);

private:
	// Search for player name in files to get his last checkpoint
	void checkOpendLevels();


	// Make available levels look special
	void setOpendLevels();


	// Get how many lines in players file
	int getNumberOfLines();


	// Move up to the previous level
	void moveUp();


	// Move to the next level
	void moveDown();
};
