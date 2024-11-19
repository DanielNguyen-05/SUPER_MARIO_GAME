#include "../header/Characters.h"

void Characters::draw(sf::RenderWindow& window)
{
    window.draw(characterSprite);
    animation();
}

void Characters::catchEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Right)
        {
            goRight = true;
        }
        if (event.key.code == sf::Keyboard::Left)
        {
            goLeft = true;
        }
        if (event.key.code == sf::Keyboard::Up)
        {
            goUp = true;
        }
        if (event.key.code == sf::Keyboard::Down)
        {
            goDown = true;
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Right)
        {
            goRight = false;
        }
        if (event.key.code == sf::Keyboard::Left)
        {
            goLeft = false;
        }
        if (event.key.code == sf::Keyboard::Up)
        {
            goUp = false;
        }
        if (event.key.code == sf::Keyboard::Down)
        {
            goDown = false;
        }
    }
}

void Characters::startDamage()
{
    damaging = true;
}

void Characters::startDie()
{
    dying = true;
}

void Characters::smallState()
{
    characterSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void Characters::bigState()
{
    characterSprite.setTextureRect(sf::IntRect(0, 16, 16, 32));
}

void Characters::superState()
{
    characterSprite.setTextureRect(sf::IntRect(0, 32, 16, 48));
}

void Characters::setCharacterRectForWalk(sf::IntRect& intRect)
{
    if (intRect.left == 0)
    {
        intRect.left = 16;
    }
    else
    {
        intRect.left = 0;
    }
}

void Characters::standStill()
{
    characterSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void Characters::move()
{
    if (goRight)
    {
        characterSprite.move(speed[0], 0);
    }
    if (goLeft)
    {
        characterSprite.move(-speed[0], 0);
    }
    if (goUp)
    {
        characterSprite.move(0, -speed[1]);
    }
    if (goDown)
    {
        characterSprite.move(0, speed[1]);
    }
}

void Characters::jump(sf::IntRect& intRect, int RectPosition, float waiting)
{
    if (goUp && onGround)
    {
        startJumpPosition = characterSprite.getPosition().y;
        onGround = false;
        characterSprite.move(0, -speed[2]);
    }
    if (!onGround)
    {
        if (characterSprite.getPosition().y <= startJumpPosition - RectPosition)
        {
            goUp = false;
            goDown = true;
        }
        if (characterSprite.getPosition().y >= startJumpPosition)
        {
            goDown = false;
            onGround = true;
            intRect.left = 0;
        }
    }
}

void Characters::moveRight(sf::IntRect& intRect)
{
    if (goRight)
    {
        setCharacterRectForWalk(intRect);
        characterSprite.move(speed[0], 0);
    }
}

void Characters::moveLeft(sf::IntRect& intRect)
{
    if (goLeft)
    {
        setCharacterRectForWalk(intRect);
        characterSprite.move(-speed[0], 0);
    }
}

void Characters::animation()
{
    if (timer1.getElapsedTime().asSeconds() > 0.1)
    {
        characterSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        timer1.restart();
    }
}

void Characters::changeToBig()
{
    if (changeStateTimer.getElapsedTime().asSeconds() > 0.1)
    {
        characterSprite.setTextureRect(sf::IntRect(0, 16, 16, 32));
        changeStateTimer.restart();
    }
}

void Characters::changeToSuper()
{
    if (changeStateTimer.getElapsedTime().asSeconds() > 0.1)
    {
        characterSprite.setTextureRect(sf::IntRect(0, 32, 16, 48));
        changeStateTimer.restart();
    }
}

void Characters::damage()
{
    if (changeStateTimer.getElapsedTime().asSeconds() > 0.1)
    {
        characterSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        changeStateTimer.restart();
    }
}

void Characters::die()
{
    if (changeStateTimer.getElapsedTime().asSeconds() > 0.1)
    {
        characterSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        changeStateTimer.restart();
    }
}

// Giảm mạng sống khi Mario chết
void Characters::loseLife() {
    if (livesLeft > 0) {
        livesLeft--;  // Giảm số mạng còn lại
    }
    else {
        dead = true;  // Mario chết hoàn toàn nếu hết mạng
    }
}

// Hồi sinh Mario từ checkpoint hoặc từ đầu level
void Characters::respawn() {
    if (livesLeft > 0) {
        if (respawnFromCheckpoint) {
            // Hồi sinh từ checkpoint
            characterSprite.setPosition(checkpointPosition);
        }
        else {
            // Hồi sinh từ đầu level
            characterSprite.setPosition(500, 200);  // Vị trí đầu level
        }
        dying = false;
        dead = false;
        onGround = true;  // Mario ở trạng thái đứng trên mặt đất
    }
}

// Thiết lập checkpoint khi Mario đạt đến vị trí đặc biệt
void Characters::setCheckpoint(sf::Vector2f position) {
    checkpointPosition = position;
    respawnFromCheckpoint = true;  // Sau khi thiết lập checkpoint, Mario sẽ hồi sinh tại đây
}
