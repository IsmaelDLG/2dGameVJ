#pragma once
#include "Sprite.h"
#include "Level.h"

class Bullet
{
public:

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setMap(Level* myMap);
	void setPosition(const glm::vec2& pos);
	void setDirection(const glm::vec2& dir) { direction = dir; }

	glm::vec2 getBulletpos() { return posBullet; }

private:
	glm::ivec2 posBullet, direction, tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;
	Level* map;
};
