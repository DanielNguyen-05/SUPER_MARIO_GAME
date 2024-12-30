// CharacterCommand.cpp
#include "../header/Characters.h"
#include "../header/CharacterCommand.h"

void MoveRightCommand::execute(Characters &character)
{
    if (!character.dying && (!character.stuck || character.facingDirection == 0))
    {
        character.goRight = true;
    }
}

void MoveLeftCommand::execute(Characters &character)
{
    if (!character.dying && (!character.stuck || character.facingDirection == 1))
    {
        character.goLeft = true;
    }
}

void JumpCommand::execute(Characters &character)
{
    if (!character.dying)
    {
        character.goUp = true;
    }
}

InputHandler::InputHandler()
{
    buttonD = new MoveRightCommand();
    buttonA = new MoveLeftCommand();
    buttonW = new JumpCommand();
    movement = new CharacterMovement();
}

InputHandler::~InputHandler()
{
    delete buttonD;
    delete buttonA;
    delete buttonW;
    delete movement;
}

void InputHandler::handleInput(Event &event, Characters &character)
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

void MoveCommand::update(Characters& character) {
    updateMovement(character);
    checkDeathBoundary(character);
    checkStandStill(character);
}

void CharacterMovement::updateMovement(Characters& character) {
    if (character.onGround) {
        character.jumping = false;
    }
    
    sf::IntRect charRect = character.charSprite.getTextureRect();
    waitingTime = 0.05;
    if (timer1.getElapsedTime().asSeconds() > waitingTime) {
        handleJump(character, charRect);
        waitingTime += 0.07;
        if (timer2.getElapsedTime().asSeconds() > waitingTime) {
            handleHorizontalMovement(character, charRect);
            timer2.restart();
        }
        character.charSprite.move(character.speed[0], character.speed[1]);
        timer1.restart();
    }
}

void CharacterMovement::handleJump(Characters& character, sf::IntRect& charRect) {
    float jumpRectPosition = character.state->getJumpRectPosition();
    
    if (character.goUp) {
        charRect.left = jumpRectPosition;
        character.charSprite.setTextureRect(charRect);
        
        if (!character.jumping) {
            character.jumpSound.play();
            character.startJumpPosition = character.charSprite.getPosition().y;
            character.speed[1] = -60;
            character.jumping = true;
        }
        character.goUp = false;
        character.onGround = false;
    }
    character.jump(charRect, jumpRectPosition, waitingTime);
}

void CharacterMovement::handleHorizontalMovement(Characters& character, sf::IntRect& charRect) {
    if (character.goRight && (!character.stuck || character.facingDirection == 0)) {
        character.moveRight(charRect);
    }
    else if (character.goLeft && (!character.stuck || character.facingDirection == 1)) {
        character.moveLeft(charRect);
    }
    else if (character.speed[0] >= 1 || character.speed[0] <= -1) {
        character.state->setCharRectForWalk(charRect);
        if (!character.jumping) {
            character.charSprite.setTextureRect(charRect);
        }
        character.speed[0] += character.acceleration[0] * waitingTime;
    }
}


void MoveCommand::checkDeathBoundary(Characters& character) {
    if (character.charSprite.getPosition().y >= character.deathBoundaryY) {
        character.dead = true;
        if(!character.dying){
        character.dieSound.play();
        }
        character.dying = character.goLeft = character.goRight = false;
        character.speed[0] = character.speed[1] = 0;
        character.charSprite.setPosition(500, 200);
    }
}

void MoveCommand::checkStandStill(Characters& character) {
    if (character.speed[0] < 1 && character.speed[0] > -1 && character.onGround) {
        character.standStill();
    }
}

    void InputHandler::update(Characters& character) {
        movement->update(character);
    }