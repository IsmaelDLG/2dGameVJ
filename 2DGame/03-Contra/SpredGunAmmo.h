#pragma once
#include "Sprite.h"
#include "Level.h"

class SpredGunAmmo
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Player* pc);
	void update(int deltaTime);
	void render();

	void setMap(Level* myMap);
	void setPosition(const glm::vec2& pos);

	bool isPickedUp() { return pickedUp; }

private:
	bool pickedUp;
	glm::ivec2 tileMapDispl, posAmmo;
	Player* player;
	Texture spritesheet;
	Sprite* sprite;
	Level* map;
};

