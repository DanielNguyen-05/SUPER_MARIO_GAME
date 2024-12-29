#include "../header/Level3.h"

Level3::Level3(GameEngine& gameEngine)
{
    // Set initial values
    this->gameEngine = &gameEngine;
    display = finished = false;
    memset(charOnGround, false, sizeof charOnGround);
    coinCnt = stoneCnt = stoneCoinCnt = quesCoinCnt = quesMashCnt = quesFlowerCnt = rockCnt = 0;
    levelWidth = 13397;

    // Set View Properites
    camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    camera.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    // Set Level's Background Properties
    backGroundTexture.loadFromFile(LEVEL2_BACKGROUND);
    backGroundTexture.setRepeated(true);
    backGroundShape.setTexture(&backGroundTexture);
    backGroundShape.setSize(Vector2f(levelWidth, WINDOW_HEIGHT));

    // Set Level's Ground Properties
    groundTexture.loadFromFile(LEVEL2_GROUND);
    setGroundProperties();

    // Set Positions
    arrangeLevelBlocks();

    gameEngine.setLevelName("Level 3");

    // Call Constructer for all coins
    for (int i = 0; i < coinCnt; i++)
        coin.push_back(*new Items(gameEngine, COIN, coinPosition[i].x, coinPosition[i].y));

    // Call Constructer for all Stone Blocks
    for (int i = 0; i < stoneCnt; i++)
    { // Null
        stone.push_back(*new Blocks(gameEngine, STONE, NONE, stonePosition[i].x, stonePosition[i].y));
        stone[i].blockSprite.setColor(Color(255, 0, 0)); // Red filter
    }

    for (int i = stoneCnt; i < (stoneCnt + stoneCoinCnt); i++)
    { // With Coin
        stone.push_back(*new Blocks(gameEngine, STONE, COIN, stoneCoinPosition[i - stoneCnt].x, stoneCoinPosition[i - stoneCnt].y));
        stone[i].blockSprite.setColor(Color(255, 0, 0)); // Red filter
    }

    // Call Constructer for all Question Blocks
    for (int i = 0; i < quesCoinCnt; i++) // With Coin
        question.push_back(*new Blocks(gameEngine, QUESTION, COIN, questCoinPosition[i].x, questCoinPosition[i].y));

    for (int i = quesCoinCnt; i < quesMashCnt + quesCoinCnt; i++) // With Coin
        question.push_back(*new Blocks(gameEngine, QUESTION, MASHROOM, questMashPosition[i - quesCoinCnt].x, questMashPosition[i - quesCoinCnt].y));

    for (int i = quesMashCnt + quesCoinCnt; i < quesFlowerCnt + quesMashCnt + quesCoinCnt; i++) // With Coin
        question.push_back(*new Blocks(gameEngine, QUESTION, FLOWER, questFLowerPosition[i - (quesMashCnt + quesCoinCnt)].x, questFLowerPosition[i - (quesMashCnt + quesCoinCnt)].y));

    // Call Constructer for all Rock Blocks
    for (int i = 0; i < rockCnt; i++)
    {
        rock.push_back(*new Blocks(gameEngine, ROCK, NONE, rockPosition[i].x, rockPosition[i].y));
        rock[i].blockSprite.setColor(Color(70, 50, 180)); // blue filter
    }

    // black.push_back(*new Enemy(gameEngine, BLACK, rock[55].blockSprite, rock[56].blockSprite, groundShape[0], 4062, 200));
    black.push_back(*new Enemy(gameEngine, BLACK, rock[60].blockSprite, rock[61].blockSprite, groundShape[1], 5000, 250));
    black.push_back(*new Enemy(gameEngine, BLACK, rock[39].blockSprite, rock[40].blockSprite, groundShape[0], 2500, 200));
    // Thêm các Enemy loại "TURTLE"
    // turtle.push_back(*new Enemy(gameEngine, TURTLE, rock[58].blockSprite, rock[59].blockSprite, groundShape[0], 4434, 200));
    turtle.push_back(*new Enemy(gameEngine, TURTLE, rock[41].blockSprite, rock[42].blockSprite, groundShape[1], 5700, 200));
    turtle.push_back(*new Enemy(gameEngine, TURTLE, rock[62].blockSprite, rock[63].blockSprite, groundShape[1], 5500, 250));
}

void Level3::draw(RenderWindow& window)
{
    if (display)
    {
        window.draw(backGroundShape);

        for (int i = 0; i < GROUNDS_NUM; i++)
        {
            checkGround(i);
            window.draw(groundShape[i]);
        }

        checkEnd();
        handleView(window);
        for (int i = 0; i < coinCnt; i++)
            coin[i].draw(window);

        for (int i = 0; i < (stoneCnt + stoneCoinCnt); i++)
            stone[i].draw(window);

        for (int i = 0; i < rockCnt; i++)
            rock[i].draw(window);

        for (int i = 0; i < quesMashCnt + quesCoinCnt + quesFlowerCnt; i++)
            question[i].draw(window);

        for (int i = 0; i < BLACK_NUM; i++)
            black[i].draw(window);

        // for (int i = 0; i < TURTLE_NUM; i++)
        //  turtle[i].draw(window);

        gameEngine->character->draw(window);
        gameEngine->draw(window);
        if (gameEngine->gameOverScreen)
            end();
    }
}

void Level3::catchEvents(Event event)
{
    if (display)
    {
        gameEngine->character->catchEvents(event);

        if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
        {
            this->end();
        }
    }
}

void Level3::start()
{
    resetLevel();
    camera.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    display = true;
    gameEngine->startCountDown();
}

void Level3::end()
{
    display = false;
    //if (finished)
     //  gameEngine->currentPlayer.level = "3";
    gameEngine->gameRunning = false;
    finished = true;
}

void Level3::resetLevel()
{
    gameEngine->reset();
    coin.clear();
    stone.clear();
    question.clear();
    rock.clear();
    black.clear();
    turtle.clear();

    // Call Constructer for all coins
    for (int i = 0; i < coinCnt; i++)
        coin.push_back(*new Items(*gameEngine, COIN, coinPosition[i].x, coinPosition[i].y));

    // Call Constructer for all Stone Blocks
    for (int i = 0; i < stoneCnt; i++)
    { // Null
        stone.push_back(*new Blocks(*gameEngine, STONE, NONE, stonePosition[i].x, stonePosition[i].y));
        stone[i].blockSprite.setColor(Color(255, 0, 0)); // Red filter
    }

    for (int i = stoneCnt; i < (stoneCnt + stoneCoinCnt); i++)
    { // With Coin
        stone.push_back(*new Blocks(*gameEngine, STONE, COIN, stoneCoinPosition[i - stoneCnt].x, stoneCoinPosition[i - stoneCnt].y));
        stone[i].blockSprite.setColor(Color(255, 0, 0)); // Red filter
    }

    // Call Constructer for all Question Blocks
    for (int i = 0; i < quesCoinCnt; i++) // With Coin
        question.push_back(*new Blocks(*gameEngine, QUESTION, COIN, questCoinPosition[i].x, questCoinPosition[i].y));

    for (int i = quesCoinCnt; i < quesMashCnt + quesCoinCnt; i++) // With Coin
        question.push_back(*new Blocks(*gameEngine, QUESTION, MASHROOM, questMashPosition[i - quesCoinCnt].x, questMashPosition[i - quesCoinCnt].y));

    for (int i = quesMashCnt + quesCoinCnt; i < quesFlowerCnt + quesMashCnt + quesCoinCnt; i++) // With Coin
        question.push_back(*new Blocks(*gameEngine, QUESTION, FLOWER, questFLowerPosition[i - (quesMashCnt + quesCoinCnt)].x, questFLowerPosition[i - (quesMashCnt + quesCoinCnt)].y));

    // Call Constructer for all Rock Blocks
    std::cout << rockCnt << "\n";
    for (int i = 0; i < rockCnt; i++)
    {
        rock.push_back(*new Blocks(*gameEngine, ROCK, NONE, rockPosition[i].x, rockPosition[i].y));
        // std::cout << i << "\t" << rockPosition[i].x << " \t" << rockPosition[i].y << "\n";
        rock[i].blockSprite.setColor(Color(70, 50, 180)); // blue filter
    }

    black.push_back(*new Enemy(*gameEngine, BLACK, rock[55].blockSprite, rock[56].blockSprite, groundShape[0], 4062, 200));
    // Reset lại trạng thái character*/
    gameEngine->character->reset();
}

void Level3::checkGround(int num)
{
    if (!gameEngine->character->dying)
    {
        if (groundShape[num].getGlobalBounds().intersects(gameEngine->character->charSprite.getGlobalBounds()))
        {
            gameEngine->character->charSprite.setPosition(gameEngine->character->charSprite.getPosition().x, groundShape[num].getGlobalBounds().top);
            gameEngine->character->onGround = true;
            charOnGround[num] = true;
        }
        else
        {
            if (charOnGround[num] && gameEngine->character->onGround)
            {
                charOnGround[num] = false;
                gameEngine->character->onGround = false;
                gameEngine->character->speed[1] = -5;
            }
        }
    }
}

void Level3::handleView(RenderWindow& window)
{
    // a + (b - a) * c
    if (/*!gameEngine->character->stuck*/ !gameEngine->character->dying)
    {
        float fr = (1 / 60.0);
        screenCenter = { screenCenter.x + (gameEngine->character->charSprite.getPosition().x - screenCenter.x) * fr * 20, 450 };

        if (screenCenter.x > WINDOW_WIDTH / 2 && screenCenter.x < levelWidth - (WINDOW_WIDTH / 2))
        {
            camera.setCenter(screenCenter.x, screenCenter.y);
            gameEngine->setHeaderPosition(screenCenter);
        }
        window.setView(camera);
    }
}

void Level3::checkEnd()
{
    Vector2f charPos = gameEngine->character->charSprite.getPosition();
    int space = 70;
    if (charPos.x < space)
    {
        gameEngine->character->charSprite.setPosition(space, charPos.y);
        gameEngine->character->speed[0] = 0;
    }
    else if (charPos.x > levelWidth - space)
    {
        finished = true;
        gameEngine->WinnerScreen = true;
        gameEngine->character->charSprite.setPosition(levelWidth - space, charPos.y);
        gameEngine->character->speed[0] = 0;
        gameEngine->addPlayerInfo(3);
        end();
    }
}

void Level3::setGroundProperties()
{
    for (int i = 0; i < GROUNDS_NUM; i++)
        groundShape[i].setTexture(&groundTexture);

    groundShape[0].setSize(Vector2f(5022, 140));
    groundShape[0].setPosition(0, 806);

    groundShape[1].setSize(Vector2f(2232, 140));
    groundShape[1].setPosition(5208, 806);

    groundShape[2].setSize(Vector2f(124, 140));
    groundShape[2].setPosition(7564, 806);

    groundShape[3].setSize(Vector2f(740, 140));
    groundShape[3].setPosition(7808, 806);

    groundShape[4].setSize(Vector2f(496, 140));
    groundShape[4].setPosition(8990, 806);

    groundShape[5].setSize(Vector2f(3488, 140));
    groundShape[5].setPosition(9900, 806);
}

void Level3::arrangeLevelBlocks()
{
    short arr[ROW_NUM][COL_NUM] = {
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 6, 6, 6, 6, 6, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 2, 6, 2, 6, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 6, 6, 6, 6, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 6, 6, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 2, 6, 2, 6, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 6, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 6, 6, 6, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 2, 6, 2, 6, 2, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 7, 3, 6, 0, 1, 1, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 6, 3, 0, 0, 0, 0, 0, 0, 2, 2, 6, 6, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 1, 2, 6, 2, 2, 6, 6, 2, 2, 2, 6, 6, 6, 2, 2, 6, 2, 6, 2, 1, 0, 0, 0, 0, 0, 0, 7, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 6, 2, 6, 2, 6, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 6, 6, 7, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 7, 7, 7, 0, 6, 0, 0, 0, 0, 0, 1, 6, 6, 2, 6, 6, 6, 6, 2, 6, 6, 6, 6, 2, 6, 0, 6, 0, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 2, 6, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 2, 2, 6, 0, 0, 0, 0, 0, 6, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 2, 2, 6, 7, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 6, 6, 6, 6, 2, 6, 6, 6, 6, 2, 6, 0, 0, 0, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 6, 0, 7, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 1, 1, 1, 1, 6, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 6, 6, 6, 6, 2, 6, 6, 6, 6, 2, 2, 6, 0, 6, 2, 1, 0, 0, 0, 0, 0, 6, 2, 2, 2, 6, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 6, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 6, 6, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 6, 6, 2, 6, 6, 2, 2, 2, 6, 6, 6, 2, 2, 2, 6, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 7, 0, 0, 0, 0, 0, 6, 6, 6, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 7, 7, 7, 7, 0, 0, 0, 2, 2, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0, 0, 6, 2, 7, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 7, 6, 7, 0, 0, 0, 2, 2, 6, 6, 6, 6, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 6, 2, 2, 2, 2, 6, 0, 0, 2, 2, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 2, 2, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 3, 2, 2, 3, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 6, 2, 6, 2, 6, 2, 7, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {2, 6, 6, 6, 6, 6, 6, 6, 6, 2, 2, 7, 0, 0, 0, 0, 0, 2, 2, 6, 0, 0, 6, 6, 6, 0, 0, 6, 6, 6, 6, 6, 6, 2, 2, 2, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 7, 0, 0, 7, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 6, 2, 2, 6, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 6, 2, 6, 2, 6, 2, 7, 7, 0, 0, 0, 0, 0, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 2, 2, 7, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 0, 7, 0, 0, 0, 0, 7, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 6, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 2, 6, 2, 6, 2, 6, 2, 6, 2, 7, 7, 0, 0, 7, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 2, 2, 2, 7, 7, 0, 0, 0, 6, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 2, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 6, 2, 6, 2, 6, 2, 6, 2, 6, 2, 7, 7, 7, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
        {
            switch (arr[i][j])
            {
            case 1:
                stoneCoinPosition[stoneCoinCnt] = { float(31 + j * 62), float(31 + i * 62) };
                stoneCoinCnt++;
                break;
            case 2:
                stonePosition[stoneCnt] = { float(31 + j * 62), float(31 + i * 62) };
                stoneCnt++;
                break;
            case 3:
                questCoinPosition[quesCoinCnt] = { float(31 + j * 62), float(31 + i * 62) };
                quesCoinCnt++;
                break;
            case 4:
                questFLowerPosition[quesFlowerCnt] = { float(31 + j * 62), float(31 + i * 62) };
                quesFlowerCnt++;
                break;
            case 5:
                questMashPosition[quesMashCnt] = { float(31 + j * 62), float(31 + i * 62) };
                quesMashCnt++;
                break;
            case 6:
                rockPosition[rockCnt] = { float(31 + j * 62), float(31 + i * 62) };
                rockCnt++;
                break;
            case 7:
                coinPosition[coinCnt] = { float(31 + j * 62), float(31 + i * 62) };
                coinCnt++;
                break;
            default:
                break;
            }
        }
    }
}