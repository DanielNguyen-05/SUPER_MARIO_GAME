#pragma once
#include "DEFINITION.h"
#include "Characters.h"

class Luigi : public Characters
{
public:
    Luigi(float x, float y) : Characters(x, y)
    {
        if (!charTexture.loadFromFile(LUIGI_CHARACTER))
        {
            std::cout << "Can't load LUIGI_CHARACTER\n";
        }
        if (!charSuperTexture.loadFromFile(LUIGI_SUPER_CHARACTER))
        {
            std::cout << "Can't load LUIGI_SUPER_CHARACTER\n";
        }
        charTexture.setSmooth(false);
        charSprite.setTexture(charTexture);
        charSprite.setPosition(x, y);
        charSprite.setScale(2, 2);
    }
};