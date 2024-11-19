#include "../header/Mario.h"

Mario::Mario(float x, float y)
{
    lives = 3;
    acceleration[0] = 57;
    acceleration[1] = 80;
    speed[0] = 0;
    speed[1] = 70;
    startJumpPosition = 500;
    changeStateCounter = 0;
    goRight = goUp = goLeft = goDown = jumping = onGround = false;
    PoweringUpToSuper = PoweringUpToBig = damaging = dying = stuck = dead = false;

    // Set Mario Sprite Properties
    if (!characterTexture.loadFromFile(MARIO_CHARACTER))
    {
        std::cout << "Can't load MARIO_CHARACTER\n";
    }
    if (!characterTexture.loadFromFile(MARIO_SUPER_CHARACTER))
    {
        std::cout << "Can't load MARIO_SUPER_CHARACTER\n";
    }
    characterTexture.setSmooth(true);
    characterSprite.setTexture(characterTexture);
    characterSprite.setPosition(x, y);
    characterSprite.setScale(2, 2);
    smallState();

    // Set Sound effect Properties
    jumpBuffer.loadFromFile(JUMP_SOUND);
    jumpSound.setBuffer(jumpBuffer);

    damageBuffer.loadFromFile(DAMAGE_SOUND);
    damageSound.setBuffer(damageBuffer);

    dieBuffer.loadFromFile(DIE_SOUND);
    dieSound.setBuffer(dieBuffer);
}

void Mario::draw(sf::RenderWindow& window)
{
    window.draw(characterSprite);
    animation();
}

void Mario::smallState()
{
    characterSprite.setTexture(characterTexture);
    characterState = SMALL;
    characterArea.width = 28;
    characterArea.height = 32;
    characterSprite.setTextureRect(sf::IntRect(0, 96, characterArea.width, characterArea.height));
    characterSprite.setOrigin(characterArea.width / 2, characterArea.height);
}

void Mario::bigState()
{
    characterSprite.setTexture(characterTexture);
    characterState = BIG;
    characterArea.width = 31;
    characterArea.height = 60;
    characterSprite.setTextureRect(sf::IntRect(0, 36, characterArea.width, characterArea.height));
    characterSprite.setOrigin(characterArea.width / 2, characterArea.height);
}

void Mario::superState()
{
    bigState();
    characterState = SUPER;
    characterSprite.setTexture(characterTexture);
}

void Mario::damage()
{
    if (damaging) {
        if (changeStateCounter < 8) {
            if (changeStateTimer.getElapsedTime().asSeconds() > 0.18) {
                if (changeStateCounter % 2 == 0) {
                    characterSprite.setTextureRect(IntRect(400, 36, 40, 60));
                }
                else {
                    characterSprite.setTextureRect(IntRect(286, 96, 30, 32));
                }
                changeStateCounter++;
                changeStateTimer.restart();
            }
        }
        else {
            if (characterState == SUPER) {
                bigState();
            }
            else {
                smallState();
            }
            changeStateCounter = 0;
            damaging = false;
        }
    }
}

void Mario::catchEvents(sf::Event& event)
{
    if (!dying) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Right) {
                goRight = true;
            }
            if (event.key.code == sf::Keyboard::Left) {
                goLeft = true;
            }
            if (event.key.code == sf::Keyboard::Up) {
                goUp = true;
            }
            if (event.key.code == sf::Keyboard::Down) {
                goDown = true;
            }
            if (event.key.code == sf::Keyboard::Space) {
                if (onGround) {
                    jumping = true;
                    jumpSound.play();
                }
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Right) {
                goRight = false;
            }
            if (event.key.code == sf::Keyboard::Left) {
                goLeft = false;
            }
        }
    }
}

void Mario::startDamage()
{
    damaging = true;
    damageSound.play();
    onGround = false;
    characterSprite.move(-50, -130);
}

void Mario::startDie()
{
    dying = true;
    dieSound.play();
    changeStateCounter = 1;
    speed[0] = 0;
    speed[1] = 0;
}

void Mario::die()
{
    if (dying) {
        onGround = false; // Mario không còn ở trên mặt đất

        // Cập nhật sprite để hiển thị trạng thái chết
        characterSprite.setTextureRect(sf::IntRect(192, 96, 30, 32));

        if (changeStateCounter == 1) {
            speed[1] = -60; // Mario nhảy lên khi chết
            characterSprite.move(-75, 0); // Di chuyển Mario sang trái (hoặc có thể di chuyển khác)
            changeStateCounter = 0;

            // Phát âm thanh khi Mario chết (giả định bạn có hàm playSound)
            // playSound("mario_die_sound");
        }

        // Mario rơi xuống dần với tốc độ giảm dần (thêm trọng lực)
        speed[1] += 5; // Tăng tốc độ rơi theo trọng lực (có thể điều chỉnh để tăng dần hoặc giảm dần)
        characterSprite.move(speed[0], speed[1] * 0.1f); // Chuyển động với tốc độ giảm dần (tăng thêm hệ số 0.1f cho hiệu ứng mượt mà)

        // Kiểm tra nếu Mario rơi ra khỏi màn hình
        if (characterSprite.getPosition().y > WINDOW_HEIGHT) {
            dead = true;  // Mario chết hoàn toàn
            dying = false; // Dừng trạng thái dying
            goLeft = goRight = goUp = goDown = false; // Dừng mọi chuyển động

            speed[0] = 0; // Dừng mọi chuyển động ngang
            speed[1] = 0; // Dừng mọi chuyển động dọc

            // Cập nhật lại vị trí của Mario tại checkpoint (hoặc đầu level)
            if (livesLeft > 0) {
                // Hồi sinh tại checkpoint
                if (checkpointPosition != sf::Vector2f(0, 0)) {
                    characterSprite.setPosition(checkpointPosition);
                }
                else {
                    // Nếu không có checkpoint, hồi sinh tại vị trí đầu level
                    characterSprite.setPosition(500, 200);  // Vị trí đầu màn
                }

                // Thiết lập lại trạng thái khi hồi sinh
                dying = false;
                dead = false;
                onGround = true; // Mario đứng trên mặt đất
            }
            else {
                // Nếu không còn mạng, chuyển sang màn game over
                GameOver();
            }
        }
    }
}


void Mario::move()
{
}

void Mario::jump(sf::IntRect& intRect, int RectPosition, float waiting)
{
}

void Mario::moveRight(sf::IntRect& intRect)
{
}

void Mario::moveLeft(sf::IntRect& intRect)
{
}

void Mario::animation()
{
    if ((!PoweringUpToBig && !PoweringUpToSuper) && !damaging) {
        move();
    }
    changeToBig();
    changeToSuper();
    damage();
    die();
}

void Mario::changeToBig()
{
}

void Mario::changeToSuper()
{
}

void setMarioRectForWalk(sf::IntRect& intRect) {

}
