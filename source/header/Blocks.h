#pragma once
#include "DEFINITION.h"
#include "GameEngine.h"
#include "Items.h"

class Blocks
{
private:
    /***			Properties				***/
    sf::IntRect blockRect, stoneRect, questionRect, bronzeRect, smashRect, rockRect;
    sf::Clock timer, popUpTimer;
    int currentRect, maxRect, movingSpeed;
    float blockHight;
    bool display, faid, isPopUp, charOn, stuckOn, popUpBlock;
    position startPos;
    block_t blockType;
    item_t itemType;
    GameEngine *gameEngine;
    Items item;

public:
    sf::Sprite blockSprite;

    Blocks(GameEngine &gameEngine, block_t blockType, item_t itemType, float x, float y); // Constructor

    /***			Methods				***/

    // Draw item on screen
    void draw(sf::RenderWindow &window);

    // start animation of popping up
    void startPopUp();

    // Smash stone block then disappear
    void smash();

private:
    // handle animation for the block
    void animation();

    // Block moving up then down.
    void popUp();

    // Check if Mario hits this block
    void checkIntersection();

    // Handle actions when Mario hits the block with his head
    void handleHitBlock();
};
