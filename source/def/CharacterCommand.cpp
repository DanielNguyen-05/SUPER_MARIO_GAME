// CharacterCommand.cpp
#include "../header/Characters.h"
#include "../header/CharacterCommand.h"

void MoveRightCommand::execute(Characters& character)
{
    if (!character.dying && (!character.stuck || character.facingDirection == 0))
    {
        character.goRight = true;
    }
}

void MoveLeftCommand::execute(Characters& character)
{
    if (!character.dying && (!character.stuck || character.facingDirection == 1))
    {
        character.goLeft = true;
    }
}

void JumpCommand::execute(Characters& character)
{
    if (!character.dying && !character.jumping)
    {
        character.goUp = true;
    }
}

InputHandler::InputHandler()
{
    buttonD = new MoveRightCommand();
    buttonA = new MoveLeftCommand();
    buttonW = new JumpCommand();
}

InputHandler::~InputHandler()
{
    delete buttonD;
    delete buttonA;
    delete buttonW;
}

void InputHandler::handleInput(Event& event, Characters& character)
{
    if (event.type == Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case Keyboard::Key::D:
        case Keyboard::Key::Right:
            buttonD->execute(character);
            break;

        case Keyboard::Key::A:
        case Keyboard::Key::Left:
            buttonA->execute(character);
            break;

        case Keyboard::Key::W:
        case Keyboard::Key::Up:
        case Keyboard::Key::Space:
            buttonW->execute(character);
            break;

        default:
            break;
        }
    }
    else if (event.type == Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case Keyboard::Key::D:
        case Keyboard::Key::Right:
            character.goRight = false;
            break;

        case Keyboard::Key::A:
        case Keyboard::Key::Left:
            character.goLeft = false;
            break;

        default:
            break;
        }
    }
}