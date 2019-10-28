#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER
#include "Enemy.h"
#include "Kimkoh.h"
#include "ShaderProgram.h"
#include <list>

class EnemyManager
{
public:
	void init(const string& path,Level* map, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
private:

private:
	Kimkoh* boss;
	list<Player*> enemies;
};

#endif

