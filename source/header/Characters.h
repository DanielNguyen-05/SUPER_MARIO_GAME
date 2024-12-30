#pragma once
#include "DEFINITION.h"
#include "CharecterCommand.h"

class Characters;

class CharacterState
{
public:
    virtual ~CharacterState() = default;
    // virtual void jump() = 0;
    virtual void handleIntRect(IntRect &intRect) = 0;
    virtual int getJumpRectPosition() = 0;
    virtual void setCharRectForWalk(IntRect &intRect) = 0;
    virtual CharacterStateEnum getState() = 0;
};

class SmallState : public CharacterState
{
public:
    // void jump() override;
    void handleIntRect(IntRect &intRect) override;
    int getJumpRectPosition() override;
    void setCharRectForWalk(IntRect &intRect) override;
    CharacterStateEnum getState() override;
};

class BigState : public CharacterState
{
public:
    // void jump() override;
    void handleIntRect(IntRect &intRect) override;
    int getJumpRectPosition() override;
    void setCharRectForWalk(IntRect &intRect) override;
    CharacterStateEnum getState() override;
};

class SuperState : public CharacterState
{
public:
    // void jump() override;
    void handleIntRect(IntRect &intRect) override;
    int getJumpRectPosition() override;
    void setCharRectForWalk(IntRect &intRect) override;
    CharacterStateEnum getState() override;
};

class Characters
{
protected:
    int changeStateCounter;
    Clock timer1, timer2, changeStateTimer;
    bool goRight, goUp, goLeft, damaging;
    float acceleration[2], startJumpPosition;
    int facingDirection;
    area charArea;
    SoundBuffer jumpBuffer, damageBuffer, dieBuffer;
    Sound jumpSound, damageSound, dieSound;
    InputHandler *inputHandler;
    CharacterState *state = nullptr;

public:
    friend class MoveRightCommand;
    friend class MoveLeftCommand;
    friend class JumpCommand;
    friend class CrouchCommand;
    friend class InputHandler;
    Texture charTexture, charSuperTexture;
    bool jumping, onGround, PoweringUpToBig, PoweringUpToSuper, dying, stuck, dead;
    float speed[2];
    Sprite charSprite;

    Characters(float x, float y);
    ~Characters();

    virtual void draw(RenderWindow &window);
    virtual void catchEvents(Event &event);
    virtual void startDamage();
    virtual void startDie();
    virtual void reset();

    void setState(CharacterStateEnum state_enum);
    CharacterStateEnum getState() const;

protected:
    virtual void smallState();
    virtual void bigState();
    virtual void superState();
    virtual void move();
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
