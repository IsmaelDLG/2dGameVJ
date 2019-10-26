#include <cmath>
#include <iostream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"
#include "Game.h"

#define SPEED 3
#define B_SIZE 16

enum BulletAnims
{
	MOVE, ENEMIE_HIT, MAP_HIT
};

void Bullet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/varied.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(B_SIZE, B_SIZE), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE, 8);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(ENEMIE_HIT, 8);
	sprite->addKeyframe(ENEMIE_HIT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(MAP_HIT, 8);
	sprite->addKeyframe(MAP_HIT, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(1);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x), float(tileMapDispl.y + posBullet.y)));
}

void Bullet::update(int deltaTime)
{
	sprite->update(deltaTime);
	posBullet.x += direction.x * SPEED;
	posBullet.y += direction.y * SPEED;
	//if (map->collisionMoveRight(posBullet, glm::ivec2(B_SIZE, B_SIZE), &posBullet.y))
		//sprite->changeAnimation(MAP_HIT);
	//else
		sprite->changeAnimation(MOVE);
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x), float(tileMapDispl.y + posBullet.y)));
}
