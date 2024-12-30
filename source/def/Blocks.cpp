#include "../header/Blocks.h"

Blocks::Blocks(GameEngine &gameEngine, BlockEnum blockType, ItemEnum itemType, float x, float y) : item(gameEngine, itemType, x, y)
{
    // Set initial values
    this->gameEngine = &gameEngine;
    this->itemType = itemType;
    this->blockType = blockType;

    questionRect = IntRect(0, 0, 32, 31);
    stoneRect = IntRect(32, 0, 32, 31);
    bronzeRect = IntRect(0, 32, 32, 31);
    rockRect = IntRect(96, 0, 32, 31);
    smashRect = IntRect(0, 0, 800, 800);

    currentRect = movingSpeed = 0;
    display = true;
    item.display = false;
    faid = isPopUp = charOn = stuckOn = popUpBlock = false;
    startPos.x = x;
    startPos.y = y;

    // Set Sprite Properties
    switch (blockType)
    {
    case QUESTION:
        blockSprite.setTexture(gameEngine.questionTexture);
        blockRect = questionRect;
        maxRect = 4;
        break;
    case STONE:
        blockSprite.setTexture(gameEngine.stoneTexture);
        blockRect = stoneRect;
        maxRect = 1;
        break;
    case ROCK:
        blockSprite.setTexture(gameEngine.stoneTexture);
        blockRect = rockRect;
        maxRect = 1;
        break;
    default:
        break; // mới thêm
    }

    blockSprite.setOrigin(blockRect.width / 2, blockRect.height / 2);
    blockSprite.setTextureRect(blockRect);
    blockSprite.setPosition(x, y);
    blockSprite.setScale(2, 2);
    blockHight = blockSprite.getGlobalBounds().height;
}

void Blocks::draw(RenderWindow &window)
{
    item.draw(window);
    if (display)
    {
        animation();
        window.draw(blockSprite);
    }
}

void Blocks::animation()
{
    if (timer.getElapsedTime().asSeconds() > 0.2f)
    {
        switch (blockType)
        {
        case QUESTION:
            blockRect.left = questionRect.left + currentRect * questionRect.width;
            break;
        case BRONZE:
            blockSprite.setTexture(gameEngine->stoneTexture);
            blockRect = bronzeRect;
            maxRect = 1;
            break;
        case STONE:
            blockRect = stoneRect;
            break;
        case ROCK:
            blockRect = rockRect;
            break;
        case SMASH:
            if (!faid)
            {
                maxRect = 6;
                currentRect = 0;
                blockRect = smashRect;
                blockSprite.setOrigin(400, 400);
                blockSprite.setTexture(gameEngine->smashTextures[currentRect]);
                blockSprite.setScale(1, 1);
                faid = true;
            }
            else
            {
                blockSprite.setTexture(gameEngine->smashTextures[currentRect]);
                if (currentRect == maxRect - 1)
                    display = false;
            }
            break; // moi them
        default:
            break; // mới thêm
        }

        blockSprite.setTextureRect(blockRect);
        currentRect++;

        if (currentRect == maxRect)
            currentRect = 0;

        timer.restart();
    }
    popUp();
    if (!faid)
        checkIntersection();
}

void Blocks::smash()
{
    blockType = SMASH;
    gameEngine->smashSound.play();
}

void Blocks::startPopUp()
{
    if (!isPopUp)
    {
        isPopUp = true;
        popUpBlock = true;

        popUpTimer.restart();
        gameEngine->popUpSound.play();
    }
}

void Blocks::popUp()
{
    if (isPopUp)
    {
        int currentTime = popUpTimer.getElapsedTime().asMilliseconds();

        if (currentTime < 150) // GoingUp Time
        {
            if (popUpBlock)
                movingSpeed += -1;
            else
            {
                if (itemType == COIN)
                    movingSpeed += -3;
                else
                    movingSpeed += -1.05;
            }
        }
        else if (currentTime < 200) // StandStill time
        {
            movingSpeed = 0;
            if (itemType == MASHROOM || itemType == FLOWER)
                movingSpeed += -1;
        }
        else if (currentTime < 350) // GoingDown Time
        {
            if (popUpBlock)
                movingSpeed += 1;
            else
            {
                if (itemType == COIN)
                    movingSpeed += 1.15;
            }
        }
        else
        {
            if (blockType == QUESTION)
                blockType = BRONZE;

            movingSpeed = 0;
            if (!popUpBlock)
            {
                isPopUp = false;        // finish all pop up
                item.blockPoped = true; // when its coin its take itself
                item.itemSprite.setPosition(startPos.x, startPos.y - (blockHight / 2) - (item.itemHeight / 2));
            }
            if (popUpBlock)
            {
                popUpBlock = false; // start item pop up
                if (itemType == MASHROOM || itemType == FLOWER)
                    gameEngine->powerUpAppearSound.play(); // start sound effect
                item.display = true;
            }

            blockSprite.setPosition(startPos.x, startPos.y);
            popUpTimer.restart();
        }
        if (popUpBlock) // blocks pop up
            blockSprite.move(0, movingSpeed);
        else // item pop up
            item.itemSprite.move(0, movingSpeed);
    }
}

void Blocks::checkIntersection()
{
    // Calculate Mario and Block bounds
    FloatRect charBounds = gameEngine->character->charSprite.getGlobalBounds(),
              blockBounds = blockSprite.getGlobalBounds();
    Vector2f charPos = gameEngine->character->charSprite.getPosition(), blockPos = blockSprite.getPosition();

    float blockTopPoint = blockPos.y - (blockBounds.height / 2),
          blockBottomPoint = blockPos.y + (blockBounds.height / 2),
          blockRightPoint = blockPos.x + (blockBounds.width / 2),
          blockLeftPoint = blockPos.x - (blockBounds.width / 2);

    // In the block bounds
    if (blockBounds.intersects(charBounds) && !gameEngine->character->dying)
    {
        if (charPos.x >= blockLeftPoint && charPos.x <= blockRightPoint)
        {
            if (gameEngine->character->speed[1] > 0 && blockType != SMASH)
            { // jump on the block
                gameEngine->character->charSprite.setPosition(charPos.x, blockBounds.top);
                gameEngine->character->onGround = true;
                charOn = true;
            }
            else if (gameEngine->character->speed[1] < 0 /*charPos.y - (charBounds.height/2) >= blockBottomPoint*/)
            { // Hit the block with head
                float blockBottom = blockBounds.top + blockBounds.height;

                // Handle large size of smash sprite
                if (blockType == SMASH)
                    blockBottom = (blockBounds.top + blockBottom) / 2;

                gameEngine->character->charSprite.setPosition(charPos.x, blockBottom + charBounds.height);
                gameEngine->character->speed[1] = 2;
                handleHitBlock();
            }
        }
        else
        { // touch from side
            if (gameEngine->character->speed[1] > 1 && !gameEngine->character->onGround || gameEngine->character->speed[1] < 1)
            {
                float blockRight = blockBounds.left + blockBounds.width;
                float blockLeft = blockBounds.left;
                float charRight = charPos.x + (charBounds.width / 2);
                float charLeft = charPos.x - (charBounds.width / 2);
                if ((charRight > blockLeft && charLeft < blockRight) &&
                    (charPos.y > (blockPos.y + 5) && charPos.y < blockPos.y + blockBounds.height))
                {

                    if (charPos.x > blockPos.x)
                    {
                        gameEngine->character->charSprite.setPosition(blockRight + (charBounds.width / 2), charPos.y);
                    }
                    else
                    {
                        gameEngine->character->charSprite.setPosition(blockBounds.left - (charBounds.width / 2), charPos.y);
                    }
                    gameEngine->character->speed[0] = 0;
                    gameEngine->character->stuck = true;
                    stuckOn = true;

                }
            }
        }
    }
    else
    {
        if (charOn && gameEngine->character->onGround)
        { // Fall when character left the block
            charOn = false;
            gameEngine->character->onGround = false;
            gameEngine->character->speed[1] = -5;
        }

        // Fix Screen vibration when character touch block side
        if (gameEngine->character->stuck && stuckOn)
        {
            if (abs(charPos.x - blockPos.x) > 60 || abs(charPos.y - blockPos.y) > 100)
            {
                gameEngine->character->stuck = false; // not touching the side anymore
                stuckOn = false;
            }
        }
    }
}

void Blocks::handleHitBlock()
{
    switch (blockType)
    {
    case STONE:
        switch (gameEngine->character->charState)
        {
        case SMALL:
            startPopUp();
            break;
        case BIG:
        case SUPER:
            smash();
            break;
        }
        break;
    case QUESTION:
        startPopUp();
        break;
    default:
        break;
    }
}