#include "Enemy.h"
#define FALL_STEP 4
#define P_SIZE 48

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

	if (pc->getPlayerPos().x < posPlayer.x) aim = glm::vec2(-1, 0);
	else aim = glm::vec2(1, 0);

}

