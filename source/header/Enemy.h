#pragma once
#include "DEFINITION.h"
#include "GameEngine.h"
#include "Bullet.h"

class Enemy {
private:
    GameEngine* gameEngine;
    Sprite* minX;
    Sprite* maxX;
    RectangleShape* ground;
    EnemyEnum enemyType;
    IntRect enemyRect, blackRect, smashedRect, turtleRect, shellRect;
    Text floatingText;
    Clock timer, textFloatTimer, turtleTimer;
    int currentRect, maxRect, floatingSpeed, killScore;
    float speed[2], scale, accSpeed;
    bool faid, isKilled, resetTime, moving, onGround, firstTime;

    // AI-related properties
    float trackingRange; // Tracking range for Mario
    enum State { IDLE, MOVING, ATTACKING, KILLED, IN_SHELL } state;


    // Thêm mảng hoặc danh sách các viên đạn
    std::vector<Bullet> bullets;  // Mảng đạn bắn ra
    bool canShoot;  // Kiểm tra xem kẻ thù có thể bắn đạn hay không

public:
    Sprite enemySprite;
    bool display;

    Enemy(GameEngine& gameEngine, EnemyEnum type, Sprite& minX, Sprite& maxX, RectangleShape& ground, float x, float y);

    void draw(RenderWindow& window);
    void updateAI();

    // Thêm phương thức để bắn đạn
    void shoot();

    // Thêm các phương thức khác nếu cần
    void updateBullets();

private:
    void animation();
    void changeDirection();
    void checkGround();
    void checkKilled();
    void setKilled();
    void checkTurtleFaid();

    // Text floating Up when kill the enemy
    void TextFloat();
};