#pragma once
#include "GameEngine.h"

class Bullet {
private:
    float speedX;
    GameEngine* gameEngine;
    float x;
    float y;

public:
    Bullet(GameEngine& gameEngine, float x, float y);
    void update();
    FloatRect getBounds() const;
    Sprite bulletSprite;

    Bullet(GameEngine* engine, float x, float y);
};
