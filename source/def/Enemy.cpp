#include "../header/Enemy.h"

Enemy::Enemy(GameEngine& gameEngine, EnemyEnum type, Sprite& minX, Sprite& maxX, RectangleShape& ground, float x, float y) {
	this->gameEngine = &gameEngine;
	this->minX = &minX;
	this->maxX = &maxX;
	this->ground = &ground;
	display = moving = firstTime = true;
	isKilled = onGround = resetTime = faid = false;
	currentRect = floatingSpeed = 0;
	maxRect = 2;
	accSpeed = 1;
	speed[0] = gameEngine.currentPlayer.enemiesSpeed * accSpeed;
	speed[1] = 70;
	enemyType = type;
	state = IDLE;

	blackRect = IntRect(0, 0, 32, 31);
	smashedRect = IntRect(64, 0, 32, 31);
	turtleRect = IntRect(0, 34, 32, 46);
	shellRect = IntRect(64, 36, 32, 42);

	enemySprite.setTexture(gameEngine.enemyTextrue);
	enemySprite.setPosition(x, y);

	switch (enemyType) {
	case BLACK:
		enemyRect = blackRect;
		killScore = 100;
		scale = 1.8;
		break;
	case TURTLE:
		enemyRect = turtleRect;
		killScore = 400;
		scale = -1.8;
		break;
	default:
		killScore = 0;
		break;
	}

	enemySprite.setTextureRect(enemyRect);
	enemySprite.setOrigin(enemyRect.width / 2, enemyRect.height);
	enemySprite.setScale(scale, abs(scale));

	floatingText.setFont(gameEngine.floatingTextFont);
	floatingText.setCharacterSize(20);
	floatingText.setStyle(Text::Bold);
	floatingText.setOrigin(9, 9);
	floatingText.setLetterSpacing(0.01);
	floatingText.setFillColor(Color(218, 18, 29));
	floatingText.setString(std::to_string(killScore));
}

void Enemy::draw(RenderWindow& window) {
	if (display) {
		updateAI();
		animation();
		if (faid)
			window.draw(floatingText);
		window.draw(enemySprite);

		// Vẽ các viên đạn
		for (size_t i = 0; i < bullets.size(); i++) {
			window.draw(bullets[i].bulletSprite);
		}
	}
}


void Enemy::updateAI() {
	float distance = abs(enemySprite.getPosition().x - gameEngine->character->charSprite.getPosition().x);

	switch (state) {
	case IDLE:
		if (distance < 100)
			state = MOVING;
		break;
	case MOVING:
		if (distance < 50)
			state = ATTACKING;
		if (isKilled)
			state = KILLED;
		break;
	case ATTACKING:
		shoot();  // Gọi phương thức để bắn đạn
		if (distance > 100)
			state = MOVING;
		if (isKilled)
			state = KILLED;
		break;
	case KILLED:
		setKilled();
		break;
	case IN_SHELL:
		checkTurtleFaid();
		break;
	default:
		break;
	}
}


void Enemy::animation() {
	if (timer.getElapsedTime().asSeconds() > 0.2f) {
		switch (enemyType) {
		case BLACK:
			enemyRect.left = blackRect.left + currentRect * blackRect.width;
			break;
		case TURTLE:
			enemyRect.left = turtleRect.left + currentRect * turtleRect.width;
			break;
		case SHELL:
			enemyRect.left = shellRect.left + currentRect * shellRect.width;
			break;
		default:
			break;
		}
		enemySprite.setTextureRect(enemyRect);
		if (moving)
			currentRect++;
		if (currentRect == maxRect)
			currentRect = 0;

		timer.restart();
	}

	if (moving)
		enemySprite.move(speed[0], speed[1]);
	changeDirection();
	checkGround();
	checkKilled();
	TextFloat();
	if (enemyType == SHELL)
		checkTurtleFaid();
	if (firstTime && enemyType != SHELL)
	{
		speed[0] = gameEngine->currentPlayer.enemiesSpeed * accSpeed;
		firstTime = false;
	}
}

void Enemy::TextFloat()
{
	if (faid)
	{
		if (!resetTime)
		{
			floatingText.setPosition(enemySprite.getPosition());
			textFloatTimer.restart();
			resetTime = true;
		}

		int currentTime = textFloatTimer.getElapsedTime().asMilliseconds();
		if (currentTime < 60)
		{
			floatingSpeed += -1;
		}
		else if (currentTime < 750)
		{
			floatingText.setFillColor(Color(219, 59, 78));
			floatingSpeed += -0.1;
		}
		else if (currentTime < 1100)
		{
			floatingText.setFillColor(Color(179, 116, 146));
			floatingSpeed += -0.1;
		}
		else
		{
			floatingText.setFillColor(Color::Transparent);
			floatingSpeed = 0; // Reseting its value

			if (enemyType == SHELL)
			{
				if (firstTime)
				{
					resetTime = false;
					firstTime = false;
				}

				faid = false;
			}
			else
				display = false;
		}
		floatingText.move(0, floatingSpeed);
	}
}

void Enemy::changeDirection() {
	if (enemySprite.getGlobalBounds().intersects(maxX->getGlobalBounds())) {
		enemySprite.setScale(-scale, abs(scale));
		speed[0] = -gameEngine->currentPlayer.enemiesSpeed * accSpeed;
	}
	if (enemySprite.getGlobalBounds().intersects(minX->getGlobalBounds())) {
		enemySprite.setScale(scale, abs(scale));
		speed[0] = gameEngine->currentPlayer.enemiesSpeed * accSpeed;
	}
}

void Enemy::checkGround() {
	if (enemySprite.getGlobalBounds().intersects(ground->getGlobalBounds())) {
		speed[1] = 0;
		if (!onGround)
			enemySprite.setPosition(enemySprite.getPosition().x, ground->getGlobalBounds().top);
		onGround = true;
	}
	else {
		speed[1] = 70;
		onGround = false;
	}
}

void Enemy::checkKilled() {
	if (!gameEngine->character->dying) {
		if (enemySprite.getGlobalBounds().intersects(gameEngine->character->charSprite.getGlobalBounds()) && !faid) {
			if (gameEngine->character->speed[1] > 1 || (enemyType == SHELL)) {
				isKilled = true;
				if (enemyType == SHELL && !moving) {
					moving = true;
					turtleTimer.restart();
				}
				else moving = false;
			}
			else {
				gameEngine->character->startDie();
			}
		}
		if (isKilled)
			setKilled();
	}
}

void Enemy::setKilled() {
	if (isKilled) {
		gameEngine->killSound.play();
		switch (enemyType) {
		case BLACK:
			enemyType = SMASHED;
			enemyRect = smashedRect;
			currentRect = 0;
			maxRect = 1;
			break;
		case TURTLE:
			enemyType = SHELL;
			enemyRect = shellRect;
			currentRect = 0;
			maxRect = 4;
			accSpeed = 4;
			speed[0] = gameEngine->currentPlayer.enemiesSpeed * accSpeed;
			firstTime = true;
			break;
		default:
			break;
		}
		faid = true;
		isKilled = false;
		gameEngine->updateScore(killScore);
	}
}

void Enemy::checkTurtleFaid() {
	if (moving && turtleTimer.getElapsedTime().asSeconds() > 10)
		display = false;
}

// CHo bắn súng
void Enemy::shoot() {
	// Kiểm tra nếu kẻ thù có thể bắn
	if (canShoot && state == ATTACKING) {
		// Kiểm tra gameEngine đã được khởi tạo chưa
		if (gameEngine != nullptr) {
			// Tạo một viên đạn mới và thiết lập vị trí bắn
			Bullet bullet(gameEngine, enemySprite.getPosition().x, enemySprite.getPosition().y);
			bullets.push_back(bullet);
			canShoot = false;  // Chỉ bắn một viên đạn một lần trong mỗi chu kỳ tấn công
		}
		else {
			std::cerr << "GameEngine chưa được khởi tạo!" << std::endl;
		}
	}
}

void Enemy::updateBullets() {
	// Cập nhật các viên đạn
	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i].update();  // Cập nhật vị trí viên đạn
		if (bullets[i].getBounds().intersects(gameEngine->character->charSprite.getGlobalBounds())) {
			// Nếu viên đạn va chạm với Mario
			gameEngine->character->startDie();  // Gọi hàm để Mario chết
			bullets.erase(bullets.begin() + i);  // Xóa viên đạn sau khi va chạm
			break;
		}
	}
}
