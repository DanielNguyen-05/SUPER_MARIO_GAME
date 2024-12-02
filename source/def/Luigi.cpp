#include "../header/Luigi.h"

Luigi::Luigi(float x, float y) {
    lives = 3;
    acceleration[0] = 57;
    acceleration[1] = 80;
    speed[0] = 0;
    speed[1] = 70;
    startJumpPosition = 500;
    changeStateCounter = 0;
    goRight = goUp = goLeft = goDown = jumping = onGround = false;
    PoweringUpToSuper = PoweringUpToBig = damaging = dying = stuck = dead = false;

    // Set Luigi Sprite Properties
    if (!characterTexture.loadFromFile(LUIGI_CHARACTER)) {
        std::cout << "Can't load LUIGI_CHARACTER\n";
    }
    if (!characterTexture.loadFromFile(LUIGI_SUPER_CHARACTER)) {
        std::cout << "Can't load LUIGI_SUPER_CHARACTER\n";
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