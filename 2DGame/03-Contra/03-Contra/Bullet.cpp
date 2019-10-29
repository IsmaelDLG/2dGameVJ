#include <cmath>
#include <iostream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"
#include "Game.h"

#define SPEED 4
#define BOSS_SPEED 1
#define B_SIZE 16

enum BulletAnims
{
	MOVE, ENEMIE_HIT, MAP_HIT
};

void Bullet::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Player* pc, bool owner)
{
	pcBullet = owner;
	if (owner) {
		spritesheet.loadFromFile("images/Bullets/Bullet.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(B_SIZE, B_SIZE), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(3);
		sprite->setAnimationSpeed(MOVE, 8);
		sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.0f));
	}
	else {
		spritesheet.loadFromFile("images/Bullets/Beam.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(B_SIZE, B_SIZE), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(3);
		sprite->setAnimationSpeed(MOVE, 8);
		sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.0f));
		sprite->addKeyframe(MOVE, glm::vec2(0.25f, 0.0f));
		sprite->addKeyframe(MOVE, glm::vec2(0.5f, 0.0f));

	}
	player = pc;
	hit = false;

	sprite->setAnimationSpeed(ENEMIE_HIT, 1);
	sprite->addKeyframe(ENEMIE_HIT, glm::vec2(0.25f, 0.0f));

	sprite->setAnimationSpeed(MAP_HIT, 1);
	sprite->addKeyframe(MAP_HIT, glm::vec2(0.75f, 0.0f));

	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBullet.x-16), float(tileMapDispl.y + posBullet.y-16)));
}

void Bullet::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (pcBullet) {
		posBullet.x += direction.x * SPEED;
		posBullet.y += direction.y * SPEED;
	}
	else {
		posBullet.x += direction.x * BOSS_SPEED;
		posBullet.y += direction.y * BOSS_SPEED;
	}
	
	
	if (!pcBullet) {
		if (player->thereIsColision(sprite->getRealMinPos(glm::vec2(B_SIZE, B_SIZE), glm::vec2(0.f,0.f)),
			sprite->getRealSize(glm::vec2(B_SIZE, B_SIZE), glm::vec2(0.f, 0.f)))) player->takeDamage(1);
	}

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
