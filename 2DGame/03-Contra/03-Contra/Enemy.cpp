#include "Enemy.h"
#define FALL_STEP 4
#define P_SIZE 48

void Enemy::update(int deltaTime) {
	posPlayer.y += FALL_STEP;
	map->collisionMoveDown(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0, FALL_STEP)),
		sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0.f, FALL_STEP)), &posPlayer.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
