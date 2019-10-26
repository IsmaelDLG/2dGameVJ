#include "EnemyManager.h"
#include <fstream>

void EnemyManager::init(ShaderProgram& shaderProgram)
{
	ifstream inf;
	string line;

	inf.open("levels/level01/enemies.txt");
	if (!inf.is_open())
		throw "Couldn't open file!";
	getline(inf, line);
	if (line.compare(0, 7, "ENEMIES") != 0)
		throw "Not an enemies file!";
		
	enemies 
}
