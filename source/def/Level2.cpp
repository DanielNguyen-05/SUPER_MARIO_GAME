#include "../header/Level2.h"

Level2::Level2(GameEngine& gameEngine) : mapStrategy(new Level2MapStrategy())
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
    backGroundTexture.loadFromFile(LEVEL1_BACKGROUND);
    backGroundTexture.setRepeated(true);
    backGroundShape.setTexture(&backGroundTexture);
    backGroundShape.setSize(Vector2f(levelWidth, WINDOW_HEIGHT));

    // Set Level's Ground Properties
    groundTexture.loadFromFile(LEVEL1_GROUND);
    setGroundProperties();

    // Set Positions
    arrangeLevelBlocks();

    gameEngine.setLevelName("Level 2");

    // Call Constructer for all coins
    for (int i = 0; i < coinCnt; i++)
        coin.push_back(*new Items(gameEngine, COIN, coinPosition[i].x, coinPosition[i].y));

    // Call Constructer for all Stone Blocks
    for (int i = 0; i < stoneCnt; i++)
    { // Null
        stone.push_back(*new Blocks(gameEngine, STONE, NONE, stonePosition[i].x, stonePosition[i].y));
        stone[i].blockSprite.setColor(Color(70, 50, 180)); // Blue filter
    }

    for (int i = stoneCnt; i < (stoneCnt + stoneCoinCnt); i++)
    { // With Coin
        stone.push_back(*new Blocks(gameEngine, STONE, COIN, stoneCoinPosition[i - stoneCnt].x, stoneCoinPosition[i - stoneCnt].y));
        stone[i].blockSprite.setColor(Color(70, 50, 180)); // Blue filter
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

    black.push_back(*new Enemy(gameEngine, BLACK, rock[55].blockSprite, rock[56].blockSprite, groundShape[0], 4062, 200));
    turtle.push_back(*new Enemy(gameEngine, TURTLE, rock[58].blockSprite, rock[59].blockSprite, groundShape[0], 4434, 200));
}

void Level2::draw(RenderWindow& window)
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

void Level2::catchEvents(Event event)
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

void Level2::start()
{
    resetLevel();
    camera.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    display = true;
    gameEngine->startCountDown();
}

void Level2::end()
{
    display = false;
    if (finished)
    {
        gameEngine->currentPlayer.level = "3";
        gameEngine->currentPlayer.level2Score = to_string(gameEngine->getScore());
    }
    gameEngine->gameRunning = false;
    finished = true;
}

void Level2::resetLevel()
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
        stone[i].blockSprite.setColor(Color(70, 50, 180)); // Blue filter
    }

    for (int i = stoneCnt; i < (stoneCnt + stoneCoinCnt); i++)
    { // With Coin
        stone.push_back(*new Blocks(*gameEngine, STONE, COIN, stoneCoinPosition[i - stoneCnt].x, stoneCoinPosition[i - stoneCnt].y));
        stone[i].blockSprite.setColor(Color(70, 50, 180)); // Blue filter
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

void Level2::checkGround(int num)
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

void Level2::handleView(RenderWindow& window)
{
    // a + (b - a) * c
    if (/*!gameEngine->character->stuck*/ !gameEngine->character->dying)
    {
        float fr = (1 / 60.0);
        screenCenter = { screenCenter.x + (gameEngine->character->charSprite.getPosition().x - screenCenter.x) * fr * 20 * 0.15f, 450 };

        if (screenCenter.x > WINDOW_WIDTH / 2 && screenCenter.x < levelWidth - (WINDOW_WIDTH / 2))
        {
            camera.setCenter(screenCenter.x, screenCenter.y);
            gameEngine->setHeaderPosition(screenCenter);
        }
        window.setView(camera);
    }
}

void Level2::checkEnd()
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
        gameEngine->character->charSprite.setPosition(levelWidth - space, charPos.y);
        gameEngine->character->speed[0] = 0;
        gameEngine->addPlayerInfo(2);
        end();
    }
}

void Level2::setGroundProperties()
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

void Level2::arrangeLevelBlocks()
{
    mapStrategy->buildMap(coinPosition, stonePosition, stoneCoinPosition,
        questCoinPosition, questMashPosition, questFLowerPosition,
        rockPosition, coinCnt, stoneCnt, stoneCoinCnt,
        quesCoinCnt, quesMashCnt, quesFlowerCnt, rockCnt);
}