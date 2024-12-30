#include "../header/Characters.h"

const float deathBoundaryY = 1100;

bool DEBUG_MODE = false;

// [0] đại diện cho x.
// [1] đại diện cho y.

Characters::Characters(float x, float y)
{
    // Init Characters motion varible
    acceleration[0] = 57;
    acceleration[1] = 80;
    speed[0] = 0;
    speed[1] = 70;
    facingDirection = 1; // 0 = left, 1 = right
    startJumpPosition = 500;
    changeStateCounter = 0;
    goRight = goUp = goLeft = goDown = jumping = onGround = false;
    PoweringUpToSuper = PoweringUpToBig = damaging = dying = stuck = dead = false;
    inputHandler = new InputHandler();

    // Set Characters Sprite Properties
    smallState();

    if (DEBUG_MODE)
    {
        debugBox.setSize(sf::Vector2f(50, 100));       // Set box size
        debugBox.setFillColor(sf::Color::Transparent); // Transparent fill
        debugBox.setOutlineThickness(2);               // Outline thickness
        debugBox.setOutlineColor(sf::Color::Red);      // Outline color
        debugBox.setPosition(x, y);                    // Initial position
    }

    // Set Sound effect Properties
    jumpBuffer.loadFromFile(JUMP_SOUND);
    jumpSound.setBuffer(jumpBuffer);

    damageBuffer.loadFromFile(DAMAGE_SOUND);
    damageSound.setBuffer(damageBuffer);

    dieBuffer.loadFromFile(DIE_SOUND);
    dieSound.setBuffer(dieBuffer);
}

void Characters::draw(RenderWindow &window)
{
    if (DEBUG_MODE)
    {
        window.draw(debugBox);
    }
    window.draw(charSprite);
    animation();
}

void Characters::animation()
{
    if ((!PoweringUpToBig && !PoweringUpToSuper) && !damaging)
        move();
    changeToBig();
    changeToSuper();
    damage();
    die();
}

void Characters::smallState()
{
    charSprite.setTexture(charTexture);
    charState = SMALL;
    charArea.width = 28;
    charArea.height = 32;
    charSprite.setTextureRect(IntRect(0, 96, charArea.width, charArea.height));
    charSprite.setOrigin(charArea.width / 2, charArea.height);
}

void Characters::bigState()
{
    charSprite.setTexture(charTexture);
    charState = BIG;
    charArea.width = 31;
    charArea.height = 60;
    charSprite.setTextureRect(IntRect(0, 36, charArea.width, charArea.height));
    charSprite.setOrigin(charArea.width / 2, charArea.height);
}

void Characters::superState()
{
    bigState();
    charState = SUPER;
    charSprite.setTexture(charSuperTexture);
}

void Characters::catchEvents(Event &event)
{
        /*switch (event.type)
        {
        case Event::KeyPressed:
            switch (event.key.code)
            {
            case Keyboard::Key::D:
            case Keyboard::Key::Right:
                goRight = true;
                break;

            case Keyboard::Key::A:
            case Keyboard::Key::Left:
                goLeft = true;
                break;

            case Keyboard::Key::W:
            case Keyboard::Key::Up:
            case Keyboard::Key::Space:
                goUp = true;
                break;

            case Keyboard::Key::S:
            case Keyboard::Key::Down:
                goDown = true;
                break;

            case Keyboard::Key::Z:
                // startDie();
                break;
            default:
                break; // mới thêm
            }
            break;

        case Event::KeyReleased:
            switch (event.key.code)
            {
            case Keyboard::Key::D:
            case Keyboard::Key::Right:
                goRight = false;
                break;

            case Keyboard::Key::A:
            case Keyboard::Key::Left:
                goLeft = false;
                break;
            default:
                break; // mới thêm
            }
            break;
        default:
            break; // mới thêm
        }*/
       inputHandler->handleInput(event, *this);
}

void Characters::move()
{
    if (onGround)
    {
        jumping = false;
    }
    IntRect charRect = charSprite.getTextureRect();

    // used timer to make motion slower
    float waitingTime = 0.05; // 0.12s to make whole round
    if (timer1.getElapsedTime().asSeconds() > waitingTime)
    {
        // Jump when press arrow up
        int jumpRectPosition = 161; // Big and Super position = 161
        if (charState == SMALL)
            jumpRectPosition += 1.5; // Small position = 162.5

        if (goUp)
        {
            charRect.left = jumpRectPosition;
            charSprite.setTextureRect(charRect);
            if (jumping == false)
            {
                jumpSound.play(); // jumping sound
                startJumpPosition = charSprite.getPosition().y;
                speed[1] = -60;
                jumping = true;
            }
            goUp = false;
            onGround = false;
        }
        jump(charRect, jumpRectPosition, waitingTime);

        waitingTime += 0.07;
        if (timer2.getElapsedTime().asSeconds() > waitingTime)
        {

            if (goRight && (!stuck || facingDirection == 0))
            { // Move to right
                moveRight(charRect);
            }

            else if (goLeft && (!stuck || facingDirection == 1))
            { // Move to left
                moveLeft(charRect);
            }
            else
            {
                // acceleration movement when release keyboard
                if (speed[0] >= 1 || speed[0] <= -1)
                {
                    setCharRectForWalk(charRect);
                    if (!jumping)
                        charSprite.setTextureRect(charRect);

                    // Calculate Characters Speed - X axis
                    speed[0] = speed[0] + acceleration[0] * waitingTime;
                }
            }

            // set down when press arrow down
            if (goDown && charState != SMALL)
            {
                goDown = false;
            }

            timer2.restart();
        }

        charSprite.move(speed[0], speed[1]);

        if (DEBUG_MODE)
        {
            debugBox.setPosition(charSprite.getPosition());
        }

        timer1.restart();
    }
    if (charSprite.getPosition().y >= deathBoundaryY)
    {
        this->dead = true;
        dying = goLeft = goRight = false;
        speed[0] = 0;
        speed[1] = 0;
        charSprite.setPosition(500, 200);
    }

    if (speed[0] < 1 && speed[0] > -1 && onGround)
    {
        standStill();
    }
}

void Characters::setCharRectForWalk(IntRect &intRect)
{
    int maxLeft = 0, picWidth = 0;

    if (charState == SMALL)
    {
        maxLeft = 99;
        picWidth = 33;
    }
    else if (charState == BIG || charState == SUPER)
    {
        maxLeft = 96;
        picWidth = 32;
    }
    else
    { /* Do Nothing */
    }

    if (intRect.left >= maxLeft)
    {
        intRect.left = picWidth;
    }
    else
    {
        intRect.left += picWidth;
    }

    return;
}

void Characters::standStill()
{
    speed[0] = 0;
    switch (charState)
    {
    case SMALL:
        smallState();
        break;
    case BIG:
        bigState();
        break;
    case SUPER:
        superState();
        break;
    default:
        break;
    }
}

void Characters::jump(IntRect &intRect, int RectPosition, float waiting)
{
    if (onGround)
    {
        speed[1] = 0;
        jumping = false;
    }
    else
    {
        if (speed[1] > 0)
            acceleration[1] = 200; // 200
        else
            acceleration[1] = 120; // 120

        // Calculate Characters Speed - Y axis
        speed[1] = speed[1] + acceleration[1] * waiting;
    }
}

void Characters::moveRight(IntRect &intRect)
{
    // check turnAround
    if (speed[0] <= -1)
    {
        intRect.left = 129; // Big and Super position
        if (charState == SMALL)
            intRect.left = 132; // Small Position
    }
    else
    {
        setCharRectForWalk(intRect);
    }

    if (!jumping)
        charSprite.setTextureRect(intRect);
    charSprite.setScale(2, 2);

    if (facingDirection != 1)
        facingDirection = 1;
    speed[0] = 21;

    // Make acceleration work in the opposite side
    if (acceleration[0] > 0)
        acceleration[0] *= -1;
}

void Characters::moveLeft(IntRect &intRect)
{
    // check turnAround
    if (speed[0] >= 1)
    {
        intRect.left = 129; // Big and Super position
        if (charState == SMALL)
            intRect.left = 132; // Small Position
    }
    else
    {
        setCharRectForWalk(intRect);
    }

    if (!jumping)
        charSprite.setTextureRect(intRect);
    charSprite.setScale(-2, 2);

    if (facingDirection != 0)
        facingDirection = 0;
    speed[0] = -21;

    // Make acceleration work in the oppsite side
    if (acceleration[0] < 0)
        acceleration[0] *= -1;
}

void Characters::changeToBig()
{
    if (PoweringUpToBig)
    {
        if (changeStateCounter < 8)
        { // The last one will be 7 (odd)
            if (changeStateTimer.getElapsedTime().asSeconds() > 0.18)
            {
                if (changeStateCounter % 2 == 0)
                    smallState();
                else
                    bigState();

                changeStateCounter++;
                changeStateTimer.restart();
            }
        }
        else
        {
            changeStateCounter = 0;
            PoweringUpToBig = false;
        }
    }
}

void Characters::changeToSuper()
{
    if (PoweringUpToSuper)
    {
        if (changeStateCounter < 8)
        { // The last one will be 7 (odd)
            if (changeStateTimer.getElapsedTime().asSeconds() > 0.18)
            {
                if (changeStateCounter % 2 == 0)
                    smallState();
                else
                    superState();

                changeStateCounter++;
                changeStateTimer.restart();
            }
        }
        else
        {
            changeStateCounter = 0;
            PoweringUpToSuper = false;
        }
    }
}

void Characters::damage()
{
    if (damaging)
    {
        if (changeStateCounter < 8)
        { // The last one will be 7 (odd)
            if (changeStateTimer.getElapsedTime().asSeconds() > 0.18)
            {
                if (changeStateCounter % 2 == 0)
                {
                    charSprite.setTextureRect(IntRect(400, 36, 40, 60));
                }
                else
                {
                    charSprite.setTextureRect(IntRect(286, 96, 30, 32));
                }

                changeStateCounter++;
                changeStateTimer.restart();
            }
        }
        else
        {
            smallState();
            changeStateCounter = 0;
            damaging = false;
        }
    }
}

void Characters::startDamage()
{
    damaging = true;
    onGround = false;   // to fall after animation finished
    damageSound.play(); // play damage sound effect
    charSprite.move(-50, -130);
}

void Characters::die()
{
    if (dying)
    {
        onGround = false; // to leave the ground
        smallState();
        charSprite.setTextureRect(IntRect(192, 96, 30, 32));
        if (changeStateCounter == 1)
        { // Execute only for the first time
            speed[1] = -60;
            charSprite.move(-75, 0);
            changeStateCounter = 0;
        }
    }
}

void Characters::startDie()
{
    dying = true;
    dieSound.play();
    changeStateCounter = 1;
    speed[0] = 0;
    speed[1] = 0;
}

void Characters::reset()
{
    // Reset Characters motion variables
    acceleration[0] = 57;
    acceleration[1] = 80;
    speed[0] = 0;
    speed[1] = 70;
    startJumpPosition = 500;
    changeStateCounter = 0;
    goRight = goUp = goLeft = goDown = jumping = onGround = false;
    PoweringUpToSuper = PoweringUpToBig = damaging = dying = stuck = dead = false;

    // Reset Characters's position and scale
    charSprite.setPosition(500, 200);
    charSprite.setScale(2, 2);
    if (DEBUG_MODE)
    {
        debugBox.setPosition(500, 200);
    }
    // Reset to small state by default
    smallState();
}
