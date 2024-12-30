// CharacterCommand.cpp
#include "../header/Characters.h" 
#include "../header/CharecterCommand.h"

void MoveRightCommand::execute(Characters& character) {
    if (!character.dying && (!character.stuck || character.facingDirection == 0)) {
        character.goRight = true;
    }
}

void MoveLeftCommand::execute(Characters& character) {
    if (!character.dying && (!character.stuck || character.facingDirection == 1)) {
        character.goLeft = true;
    }
}

void JumpCommand::execute(Characters& character) {
    if (!character.dying && !character.jumping) {
       character.goUp = true;
    }
}

void CrouchCommand::execute(Characters& character) {
    if (!character.dying && character.charState != SMALL) {
        character.goDown = true;
    }
}

InputHandler::InputHandler() {
    buttonD = new MoveRightCommand();
    buttonA = new MoveLeftCommand();
    buttonW = new JumpCommand();
    buttonS = new CrouchCommand();
}

InputHandler::~InputHandler() {
    delete buttonD;
    delete buttonA;
    delete buttonW;
    delete buttonS;
}

void InputHandler::handleInput(Event& event, Characters& character) {
    if (event.type == Event::KeyPressed) {
        switch (event.key.code) {
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

            case Keyboard::Key::S:
            case Keyboard::Key::Down:
                buttonS->execute(character);
                break;
        }
    }
    else if (event.type == Event::KeyReleased) {
        switch (event.key.code) {
            case Keyboard::Key::D:
            case Keyboard::Key::Right:
                character.goRight = false;
                break;

            case Keyboard::Key::A:
            case Keyboard::Key::Left:
                character.goLeft = false;
                break;
        }
    }
}