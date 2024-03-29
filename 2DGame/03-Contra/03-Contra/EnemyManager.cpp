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
			if (textPaths[tile - '0' - 1].substr(textPaths[tile - '0' - 1].length() - 10) == "Kimkoh.png") {
				boss = new Kimkoh();
				boss->setMap(map);
				boss->init("images/Chars/Kimkoh.png", glm::ivec2(140, 100), shaderProgram);
			}
			else {
				enemies.push_back(new Enemy());
				enemies.back()->init(textPaths[tile - '0' - 1], glm::ivec2(0.f, 0.f), shaderProgram);
				enemies.back()->setPosition(glm::vec2(blockS * j, blockS * i));
				enemies.back()->init_stats();
				enemies.back()->setMap(map);
			}
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

void EnemyManager::update(int deltaTime, list<Bullet*>& bulletes, Player* pc, ShaderProgram texProgram, Level* map, int cameraX, int cameraW)
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
				if (boss != NULL && boss->isDead()) {
					if (!(*bit)->hasHit()) {
						if (boss->thereIsColision(pos, glm::vec2(HIT_BOX_BULLET_W, HIT_BOX_BULLET_H))
							&& (*bit)->bulletOwner()) {
							boss->reduceHealth(1);
							(*bit)->bullethit();
						}
					}
				}
			}
		}

		if (!(*it)->isKilled()) {
			glm::vec2 enemyPos = (*it)->getPlayerPos();
			if (enemyPos.x <= (cameraX + cameraW) && enemyPos.x >= cameraX)
				(*it)->update(deltaTime, pc);
		}
		//else enemies.erase(it);

	}
	if (boss != NULL) {

		if (!bulletes.empty()) {
			list<Bullet*>::iterator bit;
			for (bit = bulletes.begin(); bit != bulletes.end(); bit++) {
				glm::vec2 pos = (*bit)->getBulletpos();
				pos.x += HIT_BOX_BULLET_X;
				pos.y += HIT_BOX_BULLET_Y;
				if (!boss->isDead()) {
					if (!(*bit)->hasHit()) {
						if (boss->thereIsColision(pos, glm::vec2(HIT_BOX_BULLET_W, HIT_BOX_BULLET_H))
							&& (*bit)->bulletOwner()) {
							boss->reduceHealth(1);
							(*bit)->bullethit();
						}
						else if (pc->thereIsColision(pos, glm::vec2(HIT_BOX_BULLET_W, HIT_BOX_BULLET_H)) &&
							!(*bit)->bulletOwner()) {
							pc->takeDamage(1);
						}
					}
				}
			}
		}
		boss->update(deltaTime,pc);
	}
	
}

void EnemyManager::render(int cameraX, int cameraW)
{
	list<Enemy*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		if (!(*it)->isKilled()) {
			glm::vec2 enemyPos = (*it)->getPlayerPos();
			if(enemyPos.x <= (cameraX +cameraW) && enemyPos.x >= cameraX)
			(*it)->render();
		}
		//else enemies.erase(it);
	}
	
	if (boss != NULL) {
		boss->render();
	}
}

bool EnemyManager::gameWon()
{
	if (boss != NULL && boss->isDead() && boss->timerZero() <= 0) {
		return true;
	}
	return false;
}

bool EnemyManager::getBossFiring()
{
	if (boss != NULL)
		return boss->getisFiring();
	return false;
}

bool EnemyManager::bossSpread()
{
	if (boss != NULL)
		return boss->spreadGunOn();
	return false;
}

glm::vec2 EnemyManager::getFirePos()
{
	return boss->getFirePoint();
}

void EnemyManager::setBossFiring(bool isFiring)
{
	boss->setFiring(isFiring);
}
