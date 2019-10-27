#include <cmath>
#include <iostream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "SpredGunAmmo.h"

#define A_SIZE 16
#define FALL_STEP 3

enum PlayerAnims
{
	STAND
};

void SpredGunAmmo::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Player* pc)
{
	spritesheet.loadFromFile("images/SpreadGun.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(A_SIZE, A_SIZE), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	pickedUp = false;
	player = pc;

	sprite->setAnimationSpeed(STAND, 8);
	sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posAmmo.x), float(tileMapDispl.y + posAmmo.y)));
}

void SpredGunAmmo::update(int deltaTime)
{
	sprite->update(deltaTime);
	posAmmo.y += FALL_STEP;
	glm::vec2 playerPos = player->getPlayerPos();
	if ( (((posAmmo.x <= playerPos.x + 48) && (posAmmo.x > playerPos.x)) ||
		(posAmmo.x + A_SIZE >= playerPos.x && posAmmo.x < playerPos.x)) &&
		(((posAmmo.y <= playerPos.y + 48) && (posAmmo.y > playerPos.y)) ||
		((posAmmo.y + A_SIZE >= playerPos.y) && (posAmmo.y < playerPos.y))) ) {
		pickedUp = true;
		player->activateSG();
	}
	if (map->collisionMoveDown(posAmmo, glm::ivec2(A_SIZE, A_SIZE), &posAmmo.y))
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posAmmo.x), float(tileMapDispl.y + posAmmo.y)));
		

}

void SpredGunAmmo::render()
{
	sprite->render();
}

void SpredGunAmmo::setMap(Level* myMap)
{
	map = myMap;
}

void SpredGunAmmo::setPosition(const glm::vec2& pos)
{
	posAmmo = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posAmmo.x), float(tileMapDispl.y + posAmmo.y)));
}
