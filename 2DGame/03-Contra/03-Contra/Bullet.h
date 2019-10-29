#pragma once
#include "Sprite.h"
#include "Level.h"
#include "Player.h"

class Bullet
{
public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Player* pc, bool owner);
	void update(int deltaTime);
	void render();

	void setMap(Level* myMap);
	void setPosition(const glm::vec2& pos);
	void setDirection(const glm::vec2& dir) { direction = dir; }
	void bullethit() { hit = true; }

	glm::vec2 getBulletpos() { return posBullet; }
	bool hasHit() { return hit; }
	bool bulletOwner() { return pcBullet; }

private:
	glm::ivec2 posBullet, tileMapDispl;
	glm::vec2  direction;
	bool hit;
	bool pcBullet;
	Player* player;
	Texture spritesheet;
	Sprite* sprite;
	Level* map;
};
