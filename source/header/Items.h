#pragma once
#include "DEFINITION.h"
#include "GameEngine.h"

class Items
{
private:
    /***            Properties                ***/
    GameEngine *gameEngine;
    sf::IntRect itemIntRect, coinIntRect, flowerIntRect, mashroomIntRect, sparklsIntRect;
    sf::Clock timer, textFloatTimer;
    sf::Text floatingText;
    ItemEnum itemType;
    int CurrentRect, maxRect, floatingSpeed, takenScore;
    bool faid, isTaken, resetTime;

public:
    sf::Sprite itemSprite;
    bool display, blockPoped;
    float itemHeight;

    /***            Constructor             ***/
    Items(GameEngine &gameEngine, ItemEnum item, float x, float y);

    /***            Methods                ***/

    // Draw item on screen
    void draw(sf::RenderWindow &window);

private:
    // Handle animation for the item
    void animation();

    // Text floating up when the item is taken
    void TextFloat();

    // Check if Mario has taken this item
    void checkTaken();

    // Handle what happens when the item is taken
    void setTaken();
};
