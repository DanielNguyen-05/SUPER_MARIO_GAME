// header/CharacterCommand.h
#pragma once
//#include "Characters.h"
#include <SFML/Graphics.hpp>
using namespace sf;

// Forward declaration
class Characters;

// Base Command class
class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Characters& character) = 0;
};

// Concrete Commands
class MoveRightCommand : public Command {
public:
    void execute(Characters& character) override;
};

class MoveLeftCommand : public Command {
public:
    void execute(Characters& character) override;
};

class JumpCommand : public Command {
public:
    void execute(Characters& character) override;
};




class MoveCommand {
protected:
    float waitingTime = 0.05;
    Clock timer1, timer2;
public:
    virtual void update(Characters& character);

    virtual void updateMovement(Characters& character) = 0;

    void checkDeathBoundary(Characters& character);

    void checkStandStill(Characters& character);
};

class CharacterMovement : public MoveCommand {
public:
    //void update(Characters& character);
    void updateMovement(Characters& character) override;

private:
    void handleJump(Characters& character, IntRect& charRect);

    void handleHorizontalMovement(Characters& character, IntRect& charRect);
};

// Update InputHandler to include the movement system
class InputHandler {
private:
    Command* buttonD;
    Command* buttonA;
    Command* buttonW;
    CharacterMovement* movement;

public:
    InputHandler();

    ~InputHandler();

    void update(Characters& character);
    void handleInput(Event& event, Characters& character);

    // Rest of the InputHandler implementation remains the same
};
