#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER
#include "Enemy.h"
#include "ShaderProgram.h"
#include <list>
#include "Bullet.h"

class EnemyManager
{
public:
	void init(const string& path,Level* map, ShaderProgram& shaderProgram);
	void update(int deltaTime, list<Bullet*>& bulletes, Player* pc, ShaderProgram texProgram, Level* map);
	void render();

	//void giveBullets(vector<Bullet*> bulls) { bulletes = bulls; }

private:
	Enemy* enemy1;
	Enemy* enemy2;
	list<Enemy*> enemies;
	list<Bullet*> enemyBullets;
};

#endif

