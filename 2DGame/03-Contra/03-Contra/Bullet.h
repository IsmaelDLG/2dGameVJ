#pragma once
#include "Sprite.h"
#include "Level.h"
#include "Player.h"

class Bullet
{
public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Player* pc);
	void update(int deltaTime);
	void render();

	void setMap(Level* myMap);
	void setPosition(const glm::vec2& pos);
	void setDirection(const glm::vec2& dir) { direction = dir; }
	void bullethit() { hit = true; }

	glm::vec2 getBulletpos() { return posBullet; }
	bool hasHit() { return hit; }

private:
	glm::ivec2 posBullet, direction, tileMapDispl;
	bool hit;
	Player* player;
	Texture spritesheet;
	Sprite* sprite;
	Level* map;
};
