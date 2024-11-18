#pragma once
#include "Characters.h"

// Mario's specific states and behaviors
class Mario : public Characters {
private:
    // Mario's unique properties
    sf::Texture marioTexture, marioSuperTexture; // Textures for different states
    sf::SoundBuffer jumpBuffer, damageBuffer, dieBuffer; // Sound buffers
    sf::Sound jumpSound, damageSound, dieSound; // Sounds for jumping, taking damage, and dying

    bool PoweringUpToBig, PoweringUpToSuper; // Power-up states
    bool stuck, dead; // Mario's current state

    // Private methods to change states (implemented in Mario class)
    void smallState() override;
    void bigState() override;
    void superState() override;
    void changeToBig() override;
    void changeToSuper() override;
    void damage() override;
    void die() override;

public:
    // Constructor
    Mario(float x, float y);

    // Public properties
    bool jumping, onGround, dying;
    float speed[3];
    sf::Sprite marioSprite;
    marioState_t marioState;

    // Overridden methods for Mario
    void draw(sf::RenderWindow& window) override;
    void catchEvents(sf::Event& event) override;
    void startDamage() override;
    void startDie() override;

    // Mario-specific movement methods
    void move() override;
    void jump(sf::IntRect& intRect, int RectPosition, float waiting) override;
    void setMarioRectForWalk(sf::IntRect& intRect);
    void moveRight(sf::IntRect& intRect) override;
    void moveLeft(sf::IntRect& intRect) override;

    // Handle Mario animation
    void animation() override;
};
