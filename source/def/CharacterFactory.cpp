#include "../header/CharacterFactory.h"

shared_ptr<Characters> CharacterFactory::createCharacter(CharacterTypeEnum type, float x, float y)
{
    switch (type)
    {
    case CharacterTypeEnum::MARIO:
        return make_shared<Mario>(x, y);
    case CharacterTypeEnum::LUIGI:
        return make_shared<Luigi>(x, y);
    default:
        return nullptr;
    }
}