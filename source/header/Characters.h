#pragma once
#include "DEFINITION.h"

class Characters {
protected:
    vector<Characters> characters;
    int changeStateCounter;
    bool goRight, goUp, goLeft, goDown, damaging;
    float acceleration[3], startJumpPosition;

    sf::Clock timer1, timer2, changeStateTimer;
    area characterArea;
    sf::SoundBuffer jumpBuffer, damageBuffer, dieBuffer;
    sf::Sound jumpSound, damageSound, dieSound;


    virtual void smallState(); // Set Character to Small state
    virtual void bigState(); // Set Character to Big state
    virtual void superState(); // Set Character to Super state

    virtual void setCharacterRectForWalk(sf::IntRect& intRect); // Make animation for Character while walking
    virtual void standStill(); // Make Character animation stand still 

    virtual void move(); // Character movement animation
    virtual void jump(sf::IntRect& intRect, int RectPosition, float waiting); // Make Character jump

    virtual void moveRight(sf::IntRect& intRect); // Make Character walk to the right
    virtual void moveLeft(sf::IntRect& intRect); // Make Character walk to the left

    virtual void animation(); // Make animation for Character changing

    virtual void changeToBig(); // Make animation for Power up to Big state
    virtual void changeToSuper(); // Make animation for Power up to Super state

    virtual void damage(); // Animation of converting Character from big or super state to small 
    virtual void die(); // Animation of Dying

public:
    sf::Texture characterTexture;
    bool jumping, onGround, PoweringUpToBig, PoweringUpToSuper, dying, stuck, dead;
    float speed[3];
    sf::Sprite characterSprite;
    characterState_t characterState;

    virtual ~Characters() {}
    virtual void draw(sf::RenderWindow& window);
    virtual void catchEvents(sf::Event& event);
    virtual void startDamage();
    virtual void startDie();
};
