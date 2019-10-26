#include "EnemyManager.h"
#include <fstream>
#include <sstream>


void EnemyManager::init(Level* map, ShaderProgram& shaderProgram)
{
	ifstream inf;
	stringstream ss;
	string line;
	char tile;
	int diffEnemies, blockS;
	int nEnemies;

	inf.open("levels/level01/enemies.txt");
	if (!inf.is_open())
		throw "Couldn't open file!";
	getline(inf, line);
	if (line.compare(0, 7, "ENEMIES") != 0)
		throw "Not an enemies file!";
	getline(inf, line);
	ss.str(line);
	ss >> blockS >> diffEnemies >> nEnemies;

	vector<string> textPaths = vector<string> (diffEnemies);

	for (int i = 0; i < diffEnemies; i++) {
		getline(inf, line);
		ss.str(line);
		ss >> textPaths[i];
	}
	

	
	while (line.compare(0, 6, "layer") != 0) getline(inf, line);
	
	inf.get(tile);
	int i = 0, j = 0;
	while (tile != '.')
	{
		while (tile != ';' && tile != '.')
		{
			//coma
			if (tile == ',')
				inf.get(tile);
			//enf of coma

			if (tile > '0' && tile <= '9') {
				enemies.push_back(new Enemy());
				enemies.back()->init(textPaths[tile - '0' - 1 ], glm::ivec2(0.f, 0.f), shaderProgram);
				enemies.back()->setPosition(glm::vec2(blockS * i, blockS * j));
				enemies.back()->setMap(map);
				j++;
			}
			else if (tile == '0')
				j++;
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

void EnemyManager::update(int deltaTime)
{

	list<Enemy*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->update(deltaTime);
	}
}

void EnemyManager::render()
{
	list<Enemy*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->render();
	}
}