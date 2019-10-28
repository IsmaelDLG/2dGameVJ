#include <cmath>
#include <iostream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"
#include "Game.h"

#define SPEED 4
#define B_SIZE 16

enum BulletAnims
{
	MOVE, ENEMIE_HIT, MAP_HIT
};

void Bullet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Player* pc)
{
	spritesheet.loadFromFile("images/Bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(B_SIZE, B_SIZE), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
	player = pc;
	hit = false;
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE, 8);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.0f));

	sprite->setAnimationSpeed(ENEMIE_HIT, 8);
	sprite->addKeyframe(ENEMIE_HIT, glm::vec2(0.25f, 0.0f));

	sprite->setAnimationSpeed(MAP_HIT, 8);
	sprite->addKeyframe(MAP_HIT, glm::vec2(0.75f, 0.0f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x-16), float(tileMapDispl.y + posBullet.y-16)));
}

void Bullet::update(int deltaTime)
{
	sprite->update(deltaTime);
	posBullet.x += direction.x * SPEED;
	posBullet.y += direction.y * SPEED;
	/*
	if (direction.x < 0) {
		if (direction.y < 0) {
			if (map->collisionMoveLeft(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y) ||
				map->collisionMoveUp(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y)) {
				sprite->changeAnimation(MOVE);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x - 16), float(tileMapDispl.y + posBullet.y - 16)));
			}
			else sprite->changeAnimation(MAP_HIT);
		}
		else if (direction.y > 0) {
			if (map->collisionMoveLeft(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y) ||
				map->collisionMoveDown(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y)) {
				sprite->changeAnimation(MOVE);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x - 16), float(tileMapDispl.y + posBullet.y - 16)));
			}
			else sprite->changeAnimation(MAP_HIT);
		}
		else {
			if (!map->collisionMoveLeft(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y)) {
				sprite->changeAnimation(MOVE);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x - 16), float(tileMapDispl.y + posBullet.y - 16)));
			}
			else sprite->changeAnimation(MAP_HIT);
		}
	}
	else if (direction.x > 0) {
		if (direction.y < 0) {
			if (map->collisionMoveRight(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y) ||
				map->collisionMoveUp(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y)) {
				sprite->changeAnimation(MOVE);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x - 16), float(tileMapDispl.y + posBullet.y - 16)));
			}
			else sprite->changeAnimation(MAP_HIT);
		}
		else if (direction.y > 0) {
			if (map->collisionMoveRight(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y) ||
				map->collisionMoveDown(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y)) {
				sprite->changeAnimation(MOVE);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x - 16), float(tileMapDispl.y + posBullet.y - 16)));
			}
			else sprite->changeAnimation(MAP_HIT);
		}
		else {
			if (map->collisionMoveRight(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y)) {
				sprite->changeAnimation(MOVE);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x - 16), float(tileMapDispl.y + posBullet.y - 16)));
			}
			else sprite->changeAnimation(MAP_HIT);
		}
	}*/
	if (player->thereIsColision(posBullet, B_SIZE)) player->takeDamage(1);
	//else if ()
	sprite->changeAnimation(MOVE);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x-16), float(tileMapDispl.y + posBullet.y-16)));
}

void Bullet::render()
{
	sprite->render();
}

void Bullet::setMap(Level* myMap)
{
	map = myMap;
}

void Bullet::setPosition(const glm::vec2& pos)
{
	posBullet = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x-16), float(tileMapDispl.y + posBullet.y-16)));
}
