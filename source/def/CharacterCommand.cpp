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
        }
    }
}

void MoveCommand::update(Characters& character) {
    if (timer1.getElapsedTime().asSeconds() > waitingTime) {
        updateMovement(character);
        timer1.restart();
    }
    checkDeathBoundary(character);
    checkStandStill(character);
}

void CharacterMovement::updateMovement(Characters& character) {
    if (character.onGround) {
        character.jumping = false;
    }
    
    sf::IntRect charRect = character.charSprite.getTextureRect();
    handleJump(character, charRect);
    
    waitingTime += 0.07;
    if (timer2.getElapsedTime().asSeconds() > waitingTime) {
        handleHorizontalMovement(character, charRect);
        timer2.restart();
    }
    
    character.charSprite.move(character.speed[0], character.speed[1]);
}

void CharacterMovement::handleJump(Characters& character, sf::IntRect& charRect) {
    int jumpRectPosition = character.state->getJumpRectPosition();
    
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
    /*if (character.goRight && (!character.stuck || character.facingDirection == 0)) {
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
    }*/
    // Add small buffer for collision detection
    /*const float MIN_SPEED = 0.1f;
    
    if (character.goRight && (!character.stuck || character.facingDirection == 0)) {
        character.moveRight(charRect);
        character.speed[0] = std::max(character.speed[0], MIN_SPEED);
    }
    else if (character.goLeft && (!character.stuck || character.facingDirection == 1)) {
        character.moveLeft(charRect);
        character.speed[0] = std::min(character.speed[0], -MIN_SPEED);
    }
    else if (std::abs(character.speed[0]) >= 1) {
        character.state->setCharRectForWalk(charRect);
        if (!character.jumping) {
            character.charSprite.setTextureRect(charRect);
        }
        // Smoother deceleration
        character.speed[0] += character.acceleration[0] * waitingTime * 0.8f;
    }
    
    // Reset stuck flag each frame
    character.stuck = false;*/
       // Giảm độ bám của collision
    if (character.stuck) {
        // Nếu đang bị kẹt, cho phép movement ngay lập tức khi đổi hướng
        if ((character.goRight && character.facingDirection == 0) || 
            (character.goLeft && character.facingDirection == 1)) {
            character.stuck = false;
        }
        // Reset stuck sau một khoảng thời gian ngắn
        if (timer2.getElapsedTime().asSeconds() > 0.1f) {
            character.stuck = false;
        }
    }

    if (character.goRight && (!character.stuck || character.facingDirection == 0)) {
        character.moveRight(charRect);
        // Tăng tốc độ movement để thoát khỏi collision nhanh hơn
        character.speed[0] = std::max(character.speed[0], 2.0f);
    }
    else if (character.goLeft && (!character.stuck || character.facingDirection == 1)) {
        character.moveLeft(charRect);
        // Tăng tốc độ movement để thoát khỏi collision nhanh hơn
        character.speed[0] = std::min(character.speed[0], -2.0f);
    }
    else if (std::abs(character.speed[0]) >= 1) {
        character.state->setCharRectForWalk(charRect);
        if (!character.jumping) {
            character.charSprite.setTextureRect(charRect);
        }
        // Giảm độ trơn của movement
        character.speed[0] += character.acceleration[0] * waitingTime * 1.2f;
    }
}

void MoveCommand::checkDeathBoundary(Characters& character) {
    if (character.charSprite.getPosition().y >= character.deathBoundaryY) {
        character.dead = true;
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