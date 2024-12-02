#pragma once
#include "Characters.h"
#include "DEFINITION.h"

class Luigi : public Characters {
private:
    // Private methods to change states (implemented in Luigi class)
    void smallState();
    void bigState();
    void superState();
    void changeToBig();
    void changeToSuper();
    void damage();
    void die();

public:
    // Constructore
    Luigi(float x, float y);

    // Overridden methods for Luigi
    void draw(sf::RenderWindow& window) override;
    void catchEvents(sf::Event& event) override;
    void startDamage() override;
    void startDie() override;

    // Luigi-specific movement methods
    void move() override;
    void jump(sf::IntRect& intRect, int RectPosition, float waiting) override;
    void setLuigiRectForWalk(sf::IntRect& intRect);
    void moveRight(sf::IntRect& intRect) override;
    void moveLeft(sf::IntRect& intRect) override;

    // Handle Luigi animation
    void animation() override;
};
