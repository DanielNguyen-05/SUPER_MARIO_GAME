#pragma once
#include "Characters.h"
#include "../Header/DEFINITION.h"

class Mario : public Characters {
private:

    void smallState();

    void bigState();

    void superState();

    void move();

    void setMarioRectForWalk(sf::IntRect& intRect);

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
    Mario(float x, float y);

    void draw(sf::RenderWindow& window) override;

    void catchEvents(sf::Event& event) override;

    void startDamage();

    void startDie();
};

