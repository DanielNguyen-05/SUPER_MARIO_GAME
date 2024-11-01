#pragma once
#include "../Header/DEFINITION.h"

class Characters {
protected:
    int changeStateCounter;
    sf::Clock timer1, timer2, changeStateTimer;
    bool goRight, goUp, goLeft, goDown, damaging;
    float acceleration[2], startJumpPosition;
    area characterArea;
    sf::SoundBuffer jumpBuffer, damageBuffer, dieBuffer;
    sf::Sound jumpSound, damageSound, dieSound;
    sf::Texture characterTexture;
    bool jumping, onGround, dying, stuck, dead;
    float speed[2];
    sf::Sprite characterSprite;

public:
    virtual ~Characters() {}
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void catchEvents(sf::Event& event) = 0;
};
