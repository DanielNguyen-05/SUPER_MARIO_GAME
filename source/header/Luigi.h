#pragma once
#include "Characters.h"
#include "../Header/DEFINITION.h"

class Luigi : public Characters {
private:

    void smallState();

    void bigState();

    void superState();

    void move();

    void setLuigiRectForWalk(sf::IntRect& intRect);

    void standStill();

    void jump(sf::IntRect& intRect, int RectPosition, float waiting);

    void moveRight(sf::IntRect& intRect);

    void moveLeft(sf::IntRect& intRect);

    void animation();

    void changeToBig();

    void changeToSuper();

    void damage();

    void die();

public:
    Luigi(float x, float y);

    void draw(sf::RenderWindow& window) override;

    void catchEvents(sf::Event& event) override;

    void startDamage();

    void startDie();
};
