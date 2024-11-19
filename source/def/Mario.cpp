#include "../header/Mario.h"

Mario::Mario(float x, float y)
{
    acceleration[0] = 57;
    acceleration[1] = 80;
    acceleration[2] = 93;
    speed[0] = 0;
    speed[1] = 70;
    speed[2] = 120;
    startJumpPosition = 500;
    changeStateCounter = 0;
    goRight = goUp = goLeft = goDown = jumping = onGround = false;
    PoweringUpToSuper = PoweringUpToBig = damaging = dying = stuck = dead = false;

    // Set Mario Sprite Properties
    if (!marioTexture.loadFromFile(MARIO_CHARACTER))
    {
        std::cout << "Can't load MARIO_CHARACTER\n";
    }
    if (!marioSuperTexture.loadFromFile(MARIO_SUPER_CHARACTER))
    {
        std::cout << "Can't load MARIO_SUPER_CHARACTER\n";
    }
    marioTexture.setSmooth(true);
    marioSprite.setTexture(marioTexture);
    marioSprite.setPosition(x, y);
    marioSprite.setScale(2, 2);
    smallState();

    // Set Sound effect Properties
    jumpBuffer.loadFromFile(JUMP_SOUND);
    jumpSound.setBuffer(jumpBuffer);

    damageBuffer.loadFromFile(DAMAGE_SOUND);
    damageSound.setBuffer(damageBuffer);

    dieBuffer.loadFromFile(DIE_SOUND);
    dieSound.setBuffer(dieBuffer);
}

void Mario::draw(sf::RenderWindow& window)
{
    window.draw(marioSprite);
    animation();
}

void Mario::animation()
{
    if ((!PoweringUpToBig && !PoweringUpToSuper) && !damaging)
        move();
    changeToBig();
    changeToSuper();
    damage();
    die();
}

void Mario::smallState()
{
}

void Mario::bigState()
{
}

void Mario::superState()
{
}

void Mario::changeToBig()
{
}

void Mario::changeToSuper()
{
}

void Mario::damage()
{
}

void Mario::die()
{
}

void Mario::catchEvents(sf::Event& event)
{
}

void Mario::startDamage()
{
}

void Mario::startDie()
{
}

void Mario::move()
{
}

void Mario::jump(sf::IntRect& intRect, int RectPosition, float waiting)
{
}

void Mario::moveRight(sf::IntRect& intRect)
{
}

void Mario::moveLeft(sf::IntRect& intRect)
{
}