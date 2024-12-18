#include "../header/Luigi.h"


Luigi::Luigi(float x, float y) {
    // Init Luigi motion varible
    acceleration[0] = 57;
    acceleration[1] = 80;
    speed[0] = 0;
    speed[1] = 70;
    startJumpPosition = 500;
    changeStateCounter = 0;
    goRight = goUp = goLeft = goDown = jumping = onGround = false;
    PoweringUpToSuper = PoweringUpToBig = damaging = dying = stuck = dead = false;

    // Set Luigi Sprite Properties
    if (!LuigiTexture.loadFromFile(LUIGI_CHARACTER)) { std::cout << "Can't load Luigi_CHARACTER\n"; }
    if (!LuigiSuperTexture.loadFromFile(LUIGI_SUPER_CHARACTER)) { std::cout << "Can't load Luigi_SUPER_CHARACTER\n"; }
    LuigiTexture.setSmooth(true);
    LuigiSprite.setTexture(LuigiTexture);
    LuigiSprite.setPosition(x, y);
    LuigiSprite.setScale(2, 2);
    smallState();

    //Set Sound effect Properties
    jumpBuffer.loadFromFile(JUMP_SOUND);
    jumpSound.setBuffer(jumpBuffer);

    damageBuffer.loadFromFile(DAMAGE_SOUND);
    damageSound.setBuffer(damageBuffer);

    dieBuffer.loadFromFile(DIE_SOUND);
    dieSound.setBuffer(dieBuffer);
}


void Luigi::draw(RenderWindow& window) {
    window.draw(LuigiSprite);

    animation();
}


void Luigi::animation() {
    if ((!PoweringUpToBig && !PoweringUpToSuper) && !damaging)
        move();

    changeToBig();
    changeToSuper();
    damage();
    die();
}


void Luigi::smallState() {
    LuigiSprite.setTexture(LuigiTexture);
    LuigiState = SMALL;
    LuigiArea.width = 28;
    LuigiArea.height = 32;
    LuigiSprite.setTextureRect(IntRect(0, 96, LuigiArea.width, LuigiArea.height));
    LuigiSprite.setOrigin(LuigiArea.width / 2, LuigiArea.height);
}


void Luigi::bigState() {
    LuigiSprite.setTexture(LuigiTexture);
    LuigiState = BIG;
    LuigiArea.width = 31;
    LuigiArea.height = 60;
    LuigiSprite.setTextureRect(IntRect(0, 36, LuigiArea.width, LuigiArea.height));
    LuigiSprite.setOrigin(LuigiArea.width / 2, LuigiArea.height);
}


void Luigi::superState() {
    bigState();
    LuigiState = SUPER;
    LuigiSprite.setTexture(LuigiSuperTexture);
}


void Luigi::catchEvents(Event& event) {
    if (!dying) {
        switch (event.type) {
        case Event::KeyPressed:
            switch (event.key.code)
            {
            case Keyboard::Key::Right:
                goRight = true;
                break;

            case Keyboard::Key::Left:
                goLeft = true;
                break;

            case Keyboard::Key::Space:
                goUp = true;
                break;

            case Keyboard::Key::Down:
                goDown = true;
                break;
            case Keyboard::Key::Z:
                //startDie();
                break;
            }
            break;

        case Event::KeyReleased:
            switch (event.key.code)
            {
            case Keyboard::Key::Right:
                goRight = false;
                break;

            case Keyboard::Key::Left:
                goLeft = false;
                break;
            }
            break;
        }
    }
}


void Luigi::move() {

    if (onGround) jumping = false;
    IntRect LuigiRect = LuigiSprite.getTextureRect();

    // used timer to make motion slower
    float waitingTime = 0.05; // 0.12s to make whole round
    if (timer1.getElapsedTime().asSeconds() > waitingTime)
    {
        // Jump when press arrow up
        int jumpRectPosition = 161; // Big and Super position = 161
        if (LuigiState == SMALL) jumpRectPosition += 1.5; // Small position = 162.5

        if (goUp) {
            LuigiRect.left = jumpRectPosition;
            LuigiSprite.setTextureRect(LuigiRect);
            if (jumping == false) {
                jumpSound.play(); // jumping sound
                startJumpPosition = LuigiSprite.getPosition().y;
                speed[1] = -60;
                jumping = true;
            }
            goUp = false;
            onGround = false;
        }
        jump(LuigiRect, jumpRectPosition, waitingTime);

        waitingTime += 0.07;
        if (timer2.getElapsedTime().asSeconds() > waitingTime) {

            if (goRight) { // Move to right
                moveRight(LuigiRect);
            }

            else if (goLeft) { // Move to left
                moveLeft(LuigiRect);
            }
            else {
                // acceleration movement when release keyboard
                if (speed[0] >= 1 || speed[0] <= -1) {
                    setLuigiRectForWalk(LuigiRect);
                    if (!jumping) LuigiSprite.setTextureRect(LuigiRect);

                    // Calculate Luigi Speed - X axis
                    speed[0] = speed[0] + acceleration[0] * waitingTime;
                }
            }

            // set down when press arrow down
            if (goDown && LuigiState != SMALL) {

                goDown = false;
            }

            timer2.restart();
        }

        LuigiSprite.move(speed[0], speed[1]);

        timer1.restart();
    }

    if (speed[0] < 1 && speed[0] > -1 && onGround) {
        standStill();
    }
}


void Luigi::setLuigiRectForWalk(IntRect& intRect) {
    int maxLeft = 0, picWidth = 0;

    if (LuigiState == SMALL)
    {
        maxLeft = 99;
        picWidth = 33;
    }
    else if (LuigiState == BIG || LuigiState == SUPER)
    {
        maxLeft = 96;
        picWidth = 32;
    }
    else {/* Do Nothing */ }

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

void Luigi::standStill() {
    speed[0] = 0;
    switch (LuigiState)
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


void Luigi::jump(IntRect& intRect, int RectPosition, float waiting) {
    if (onGround) {
        speed[1] = 0;
        jumping = false;
    }
    else {
        if (speed[1] > 0)
            acceleration[1] = 200;//200
        else
            acceleration[1] = 120;//120

        // Calculate Luigi Speed - Y axis
        speed[1] = speed[1] + acceleration[1] * waiting;
    }
}


void Luigi::moveRight(IntRect& intRect) {
    // check turnAround
    if (speed[0] <= -1) {
        intRect.left = 129; // Big and Super position
        if (LuigiState == SMALL) intRect.left = 132; // Small Position	
    }
    else {
        setLuigiRectForWalk(intRect);
    }

    if (!jumping) LuigiSprite.setTextureRect(intRect);
    LuigiSprite.setScale(2, 2);

    speed[0] = 21;

    // Make acceleration work in the opposite side
    if (acceleration[0] > 0) acceleration[0] *= -1;
}


void Luigi::moveLeft(IntRect& intRect) {
    // check turnAround
    if (speed[0] >= 1) {
        intRect.left = 129; // Big and Super position
        if (LuigiState == SMALL) intRect.left = 132; // Small Position	
    }
    else {
        setLuigiRectForWalk(intRect);
    }

    if (!jumping) LuigiSprite.setTextureRect(intRect);
    LuigiSprite.setScale(-2, 2);

    speed[0] = -21;

    // Make acceleration work in the oppsite side
    if (acceleration[0] < 0) acceleration[0] *= -1;
}


void Luigi::changeToBig() {
    if (PoweringUpToBig) {
        if (changeStateCounter < 8) { // The last one will be 7 (odd)
            if (changeStateTimer.getElapsedTime().asSeconds() > 0.18) {
                if (changeStateCounter % 2 == 0)
                    smallState();
                else
                    bigState();

                changeStateCounter++;
                changeStateTimer.restart();
            }
        }
        else {
            changeStateCounter = 0;
            PoweringUpToBig = false;
        }
    }
}


void Luigi::changeToSuper() {
    if (PoweringUpToSuper) {
        if (changeStateCounter < 8) { // The last one will be 7 (odd)
            if (changeStateTimer.getElapsedTime().asSeconds() > 0.18) {
                if (changeStateCounter % 2 == 0)
                    smallState();
                else
                    superState();

                changeStateCounter++;
                changeStateTimer.restart();
            }
        }
        else {
            changeStateCounter = 0;
            PoweringUpToSuper = false;
        }
    }
}


void Luigi::damage() {
    if (damaging) {
        if (changeStateCounter < 8) { // The last one will be 7 (odd)
            if (changeStateTimer.getElapsedTime().asSeconds() > 0.18) {
                if (changeStateCounter % 2 == 0) {
                    LuigiSprite.setTextureRect(IntRect(400, 36, 40, 60));
                }
                else {
                    LuigiSprite.setTextureRect(IntRect(286, 96, 30, 32));
                }

                changeStateCounter++;
                changeStateTimer.restart();
            }
        }
        else {
            smallState();
            changeStateCounter = 0;
            damaging = false;
        }
    }
}


void Luigi::startDamage() {
    damaging = true;
    onGround = false; // to fall after animation finished
    damageSound.play(); // play damage sound effect
    LuigiSprite.move(-50, -130);
}


void Luigi::die() {
    if (dying) {
        onGround = false; // to leave the ground 

        LuigiSprite.setTextureRect(IntRect(192, 96, 30, 32));
        if (changeStateCounter == 1) { // Execute only for the first time
            speed[1] = -60;
            LuigiSprite.move(-75, 0);
            changeStateCounter = 0;
        }
        if (LuigiSprite.getPosition().y > 900) {
            dead = true;
            dying = goLeft = goRight = false;
            speed[0] = 0;
            speed[1] = 0;
            LuigiSprite.setPosition(500, 200);
        }
    }
}


void Luigi::startDie() {
    dying = true;
    dieSound.play();
    changeStateCounter = 1;
    speed[0] = 0;
    speed[1] = 0;
}