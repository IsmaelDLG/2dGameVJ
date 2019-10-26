#ifndef _ENEMY_MANAGER_
#define _ENEMY_MANAGER
#include "Enemy.h"
#include "ShaderProgram.h"

class EnemyManager
{
public:
	void init(ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	void setMap(Level* map);
private:
	vector<Enemy> enemies;
};

#endif

