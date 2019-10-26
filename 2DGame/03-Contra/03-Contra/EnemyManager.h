#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER
#include "Enemy.h"
#include "ShaderProgram.h"
#include <list>

class EnemyManager
{
public:
	void init(Level* map, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
private:

private:
	list<Enemy*> enemies;
};

#endif

