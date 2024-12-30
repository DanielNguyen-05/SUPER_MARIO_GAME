// header/CharacterCommand.h
#pragma once
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

class CrouchCommand : public Command {
public:
    void execute(Characters& character) override;
};

// Input Handler class
class InputHandler {
private:
    Command* buttonD;
    Command* buttonA;
    Command* buttonW;
    Command* buttonS;

public:
    InputHandler();
    ~InputHandler();
    void handleInput(Event& event, Characters& character);
};