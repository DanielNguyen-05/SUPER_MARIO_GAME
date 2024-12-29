#pragma once
#include <memory>
#include "Characters.h"
#include "Mario.h"
#include "Luigi.h"

using namespace std;

class CharacterFactory
{
public:
    static shared_ptr<Characters> createCharacter(CharacterTypeEnum type, float x = 500, float y = 200);
};
