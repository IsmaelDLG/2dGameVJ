#include "EnemyManager.h"
#include <fstream>
#include <sstream>

#define HIT_BOX_BULLET_X 6
#define HIT_BOX_BULLET_Y 6
#define HIT_BOX_BULLET_H 3
#define HIT_BOX_BULLET_W 5


void EnemyManager::init(const string& path,Level* map, ShaderProgram& shaderProgram)
{
	ifstream inf;
	stringstream ss;
	string line;
	char tile;
	int diffEnemies, blockS;
	int nEnemies;

	inf.open(path);
	if (!inf.is_open())
		throw "Couldn't open file, idiot!";
	getline(inf, line);
	if (line.compare(0, 7, "ENEMIES") != 0)
		throw "Not an enemies file!";
	getline(inf, line);
	ss.str(line);
	ss >> blockS >> diffEnemies;

	vector<string> textPaths = vector<string> (diffEnemies);
	
	for (int i = 0; i < diffEnemies; i++) {
		getline(inf, line);
		textPaths[i] = line.substr(0, line.find(".png") + 4);
	}

	while (line.compare(0, 6, "layer") != 0) getline(inf, line);
	
	int i = 0, j;
	inf.get(tile);
	while (tile != '.')
	{
		j = 0;
		while (tile != ';' && tile != '.')
		{
			if (tile > '0' && tile <= '9') {
				enemies.push_back(new Enemy());
				enemies.back()->init(textPaths[tile - '0' - 1 ], glm::ivec2(0.f, 0.f), shaderProgram);
				enemies.back()->setPosition(glm::vec2(blockS * j , blockS * 0));
				enemies.back()->init_stats();
				enemies.back()->setMap(map);
				j++;
			}
			else if (tile == '0') j++;		
			inf.get(tile);

		}
		i++;
		inf.get(tile);
#ifndef _WIN32
		inf.get(tile);
#endif
	}		
	inf.close();
}

void EnemyManager::update(int deltaTime, list<Bullet*>& bulletes, Player* pc, ShaderProgram texProgram, Level* map)
{

	list<Enemy*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		if (!bulletes.empty()) {
			list<Bullet*>::iterator bit;
			for (bit = bulletes.begin(); bit != bulletes.end(); bit++) {
				glm::vec2 pos = (*bit)->getBulletpos();
				pos.x += HIT_BOX_BULLET_X;
				pos.y += HIT_BOX_BULLET_Y;
				if (!(*it)->isKilled()) {
					if (!(*bit)->hasHit()) {
						if ((*it)->thereIsColision(pos, glm::vec2(HIT_BOX_BULLET_W, HIT_BOX_BULLET_H)) 
							&& (*bit)->bulletOwner()) {
							(*it)->reduceDamage(1);
							(*bit)->bullethit();
						}
					}
				}
			}
		}
		
		/*
		if (pc->getPlayerPos().x - (*it)->getPlayerPos().x < 30) {
			(*it)->shootNow();
			if ((*it)->isShooting()) {
				glm::vec2 position = (*it)->getFirePoint();
				Bullet* bullet = new Bullet();
				bullet->init(glm::ivec2(0.f, 0.f), texProgram, pc, false);
				bullet->setPosition(glm::vec2(position.x, position.y));
				bullet->setDirection((*it)->aimingAt());
				bullet->setMap(map);
				enemyBullets.push_back(bullet);
			}
		}
		*/

		if (!(*it)->isKilled())
			(*it)->update(deltaTime, pc);
		//else enemies.erase(it);
		if (!enemyBullets.empty()) {
			list<Bullet*>::iterator it;
			for (it = enemyBullets.begin(); it != enemyBullets.end(); it++) {
				glm::vec2 posB = (*it)->getBulletpos();
				if (!(*it)->hasHit()) {
					if (/*posB.x <= offsetMaxX && posB.x >= offsetMinX &&*/ !(*it)->hasHit())
						(*it)->update(deltaTime);
				}
			}
		}
	}
}

void EnemyManager::render()
{
	list<Enemy*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		if (!(*it)->isKilled())
			(*it)->render();
		//else enemies.erase(it);
	}
	if (!enemyBullets.empty()) {
		list<Bullet*>::iterator it;
		for (it = enemyBullets.begin(); it != enemyBullets.end(); it++) {
			glm::vec2 posB = (*it)->getBulletpos();
			if (!(*it)->hasHit()) {
				if (/*posB.x <= offsetMaxX && posB.x >= offsetMinX &&*/ !(*it)->hasHit())
					(*it)->render();
			}
		}
	}
}
