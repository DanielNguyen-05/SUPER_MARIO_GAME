#pragma once
#include "DEFINITION.h"

class Luigi
{
    /***		Luigi properties		***/
private:
    int changeStateCounter;
    Clock timer1, timer2, changeStateTimer;
    bool goRight, goUp, goLeft, goDown, damaging;
    float acceleration[2], startJumpPosition;
    area LuigiArea;
    SoundBuffer jumpBuffer, damageBuffer, dieBuffer;
    Sound jumpSound, damageSound, dieSound;

public:
    Texture LuigiTexture, LuigiSuperTexture;
    bool jumping, onGround, PoweringUpToBig, PoweringUpToSuper, dying, stuck, dead;
    float speed[2];
    Sprite LuigiSprite;
    characterState_t LuigiState;

    Luigi(float x, float y); // Constractor

    /***			Methods			***/

    // Draw Luigi on screen
    void draw(RenderWindow &window);

    // Handle events for Luigi movement
    void catchEvents(Event &event);

    // Start Damage animation
    void startDamage();

    // Start Die Animation
    void startDie();

private:
    // set Luigi to small state
    void smallState();

    // set Luigi to Big state
    void bigState();

    // set Luigi to Super state
    void superState();

    // Luigi movement animation
    void move();

    // Make animation for Luigi while walking
    void setLuigiRectForWalk(IntRect &intRect);

    // Make Luigi animation stand still
    void standStill();

    // make Luigi jump
    void jump(IntRect &intRect, int RectPosition, float waiting);

    // make Luigi walk to the right
    void moveRight(IntRect &intRect);

    // make Luigi walk to the left
    void moveLeft(IntRect &intRect);

    // Make animation for Luigi changing
    void animation();

    // make animation for Power up to Big state
    void changeToBig();

    // make animation for Power up to Super state
    void changeToSuper();

    // Animation of converting Luigi from big or super state to small
    void damage();

    // Animation of Dying
    void die();
};
