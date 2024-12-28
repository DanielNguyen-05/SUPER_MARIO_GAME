#include "../header/Bullet.h"

Bullet::Bullet(GameEngine& gameEngine, float x, float y) {
    this->gameEngine = &gameEngine;
    bulletSprite.setTexture(gameEngine.bulletTexture);
    bulletSprite.setPosition(x, y);  // Vị trí bắt đầu của viên đạn
    speedX = 5.0f;  // Tốc độ của viên đạn
}

void Bullet::update() {
    bulletSprite.move(speedX, 0);  // Di chuyển viên đạn sang phải
}

FloatRect Bullet::getBounds() const {
    return bulletSprite.getGlobalBounds();  // Trả về phạm vi của viên đạn
}

Bullet::Bullet(GameEngine* engine, float x, float y) {
    // Khởi tạo Bullet, có thể sử dụng engine để thiết lập các thuộc tính khác
    this->gameEngine = engine;
    this->x = x;
    this->y = y;
}