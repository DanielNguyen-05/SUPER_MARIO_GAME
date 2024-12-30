#pragma once
#include "MapStrategy.h"
#include "Level1MapStrategy.h"
#include "DEFINITION.h"
#include "Blocks.h"
#include "Enemy.h"

#define COINS_NUM 1500
#define STONE_NUM 1500
#define STONE_WITH_COIN_NUM 1500
#define QUESTION_WITH_COIN_NUM 1500
#define QUESTION_WITH_MASH_NUM 1500
#define QUESTION_WITH_FLOWER_NUM 1500
#define ROCK_NUM 1500
#define GROUNDS_NUM 6
#define BLACK_NUM 1
#define TURTLE_NUM 1
#define ROW_NUM 14
#define COL_NUM 300

class Level1
{
    /***            Properties                ***/
private:
    vector<Items> coin;
    vector<Blocks> stone, question, rock;
    vector<Enemy> black, turtle;
    GameEngine* gameEngine;
    position coinPosition[COINS_NUM], stonePosition[STONE_NUM], stoneCoinPosition[STONE_WITH_COIN_NUM],
        questCoinPosition[QUESTION_WITH_COIN_NUM], questMashPosition[QUESTION_WITH_MASH_NUM],
        questFLowerPosition[QUESTION_WITH_FLOWER_NUM], rockPosition[ROCK_NUM];
    bool charOnGround[GROUNDS_NUM];
    float levelWidth;
    int coinCnt, stoneCnt, stoneCoinCnt, quesCoinCnt, quesMashCnt, quesFlowerCnt, rockCnt;
    sf::Texture backGroundTexture, groundTexture;
    sf::RectangleShape backGroundShape, groundShape[GROUNDS_NUM];
    position screenCenter = { 0, 0 };
    sf::View camera;

    // Strategy Pattern
    MapStrategy* mapStrategy;

public:
    bool display, finished;
    Level1(GameEngine& gameEngine);

    /***            Methods                ***/
    // Draw Levels contents
    void draw(sf::RenderWindow& window);

    // Control all level events
    void catchEvents(sf::Event event);

    // Start the Level
    void start();

    // Close the Level
    void end();

    // Check if Mario is on the ground
    void checkGround(int num);

    // Set Camera View with Mario's movement
    void handleView(sf::RenderWindow& window);

    // Check end of the level
    void checkEnd();

    ~Level1() {
        delete mapStrategy;
    }

private:
    // Arrange Array for Grounds Properties on screen
    void setGroundProperties();

    // Set Positions for all blocks in the level
    void arrangeLevelBlocks();

    void resetLevel();
};
