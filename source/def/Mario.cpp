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
    if (!characterTexture.loadFromFile(MARIO_CHARACTER))
    {
        std::cout << "Can't load MARIO_CHARACTER\n";
    }
    if (!characterTexture.loadFromFile(MARIO_SUPER_CHARACTER))
    {
        std::cout << "Can't load MARIO_SUPER_CHARACTER\n";
    }
    characterTexture.setSmooth(true);
    characterSprite.setTexture(characterTexture);
    characterSprite.setPosition(x, y);
    characterSprite.setScale(2, 2);
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
    window.draw(characterSprite);
    animation();
}

void Mario::smallState()
{
    characterSprite.setTexture(characterTexture);
    characterState = SMALL;
    characterArea.width = 28;
    characterArea.height = 32;
    characterSprite.setTextureRect(sf::IntRect(0, 96, characterArea.width, characterArea.height));
    characterSprite.setOrigin(characterArea.width / 2, characterArea.height);
}

void Mario::bigState()
{
    characterSprite.setTexture(characterTexture);
    characterState = BIG;
    characterArea.width = 31;
    characterArea.height = 60;
    characterSprite.setTextureRect(sf::IntRect(0, 36, characterArea.width, characterArea.height));
    characterSprite.setOrigin(characterArea.width / 2, characterArea.height);
}

void Mario::superState()
{
    bigState();
    characterState = SUPER;
    characterSprite.setTexture(characterTexture);
}

void Mario::damage()
{
}

void Mario::die()
{
    dying = true;
    dieSound.play();
    changeStateCounter = 1;
    speed[0] = 0;
    speed[1] = 0;
    speed[2] = 0;
}

void Mario::catchEvents(sf::Event& event)
{
}

void Mario::startDamage()
{
    damaging = true;
    onGround = false;
    damageSound.play();
    characterSprite.move(-50, -130);
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

void Mario::animation()
{
    if ((!PoweringUpToBig && !PoweringUpToSuper) && !damaging) {
        move();
    }
    changeToBig();
    changeToSuper();
    damage();
    die();
}

void Mario::changeToBig()
{
}

void Mario::changeToSuper()
{
}