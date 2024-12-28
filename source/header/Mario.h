#pragma once
#include "DEFINITION.h"
#include "Characters.h"

class Mario : public Characters
{
public:
    Mario(float x, float y) : Characters(x, y)
    {
        if (!charTexture.loadFromFile(MARIO_CHARACTER))
        {
            std::cout << "Can't load MARIO_CHARACTER\n";
        }
        if (!charSuperTexture.loadFromFile(MARIO_SUPER_CHARACTER))
        {
            std::cout << "Can't load MARIO_SUPER_CHARACTER\n";
        }
        charTexture.setSmooth(false);
        charSprite.setTexture(charTexture);
        charSprite.setPosition(x, y);
        charSprite.setScale(2, 2);
    }
};