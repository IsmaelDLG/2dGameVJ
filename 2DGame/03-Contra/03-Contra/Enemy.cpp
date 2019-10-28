#include "Enemy.h"
#define FALL_STEP 4
#define P_SIZE 48
#define HIT_BOX_X 23
#define HIT_BOX_Y 9
#define HIT_BOX_H 38
#define HIT_BOX_W 15

void Enemy::init_stats() {
	death = false;
	life = 5;
	reload = 16;
	aim = glm::vec2(0,1);
}

void Enemy::reduceDamage(int dmg) {
	life -= dmg;
	if (life <= 0) {
		death = true;
	}
}

void Enemy::shootNow()
{
	if (reload == 0) {
		shoot = true;
		reload = 16;
	}
	else {
		reload--;
		shoot = false;
	}
}

glm::vec2 Enemy::aimingAt()
{
	return aim;
}

void Enemy::update(int deltaTime, Player* pc) {
	posPlayer.y += FALL_STEP;
	map->collisionMoveDown(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0, FALL_STEP)),
		sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0.f, FALL_STEP)), &posPlayer.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	

	int dist = this->posPlayer.x - pc->getPlayerPos().x;
	glm::vec2 realPosPlayer = glm::vec2(posPlayer.x + HIT_BOX_X, posPlayer.y + HIT_BOX_Y);
	if (map->damages(realPosPlayer, sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-1, 0))))
		this->reduceDamage(9999);


	if (dist <= 128 && dist > 0) {
		aim = glm::vec2(-1, 0);
		posPlayer.x -= 1;
		if (map->collisionMoveLeft(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-1, 0)),
			sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-1, 0)), &posPlayer.y)) {
			posPlayer.x += 1;
		}
		
		if (pc->thereIsColision(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-1, 0)),
			sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-1, 0)))) {
			pc->takeDamage(1);
		}
	}
	else if (dist >= -128 && dist < 0) {
		posPlayer.x += 1;
		if (map->collisionMoveRight(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(1, 0)),
			sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(1, 0)), &posPlayer.y))
		{
			posPlayer.x -= 1;
		}
		if (pc->thereIsColision(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(1, 0)),
			sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(1, 0)))) {
			pc->takeDamage(1);
		}
	}

	
	//else aim = glm::vec2(1, 0);

}

