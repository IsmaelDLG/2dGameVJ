#include "Enemy.h"
#define FALL_STEP 4
#define P_SIZE 48

void Enemy::update(int deltaTime) {
	posPlayer.y += FALL_STEP;
	map->collisionMoveDown(posPlayer, glm::ivec2(P_SIZE, P_SIZE), &posPlayer.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
