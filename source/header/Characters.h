#pragma once
#include "DEFINITION.h"

class Characters
{
protected:
    int changeStateCounter;
    Clock timer1, timer2, changeStateTimer;
    bool goRight, goUp, goLeft, goDown, damaging;
    float acceleration[2], startJumpPosition;
    area charArea;
    SoundBuffer jumpBuffer, damageBuffer, dieBuffer;
    Sound jumpSound, damageSound, dieSound;
    sf::RectangleShape debugBox;

public:
    Texture charTexture, charSuperTexture;
    bool jumping, onGround, PoweringUpToBig, PoweringUpToSuper, dying, stuck, dead;
    float speed[2];
    Sprite charSprite;
    CharacterStateEnum charState;

    Characters(float x, float y);

    // Methods
    virtual void draw(RenderWindow &window);
    virtual void catchEvents(Event &event);
    virtual void startDamage();
    virtual void startDie();
    virtual void reset();

protected:
    virtual void smallState();
    virtual void bigState();
    virtual void superState();
    virtual void move();
    virtual void setCharRectForWalk(IntRect &intRect);
    virtual void standStill();
    virtual void jump(IntRect &intRect, int RectPosition, float waiting);
    virtual void moveRight(IntRect &intRect);
    virtual void moveLeft(IntRect &intRect);
    virtual void animation();
    virtual void changeToBig();
    virtual void changeToSuper();
    virtual void damage();
    virtual void die();
};
