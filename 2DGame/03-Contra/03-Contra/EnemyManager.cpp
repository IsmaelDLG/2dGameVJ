#include "EnemyManager.h"
#include <fstream>
#include <sstream>


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
				ofstream out;
				out.open("myDebug/manager.txt", ios::app);
				out << textPaths[tile - '0' - 1] << endl << textPaths[tile - '0' - 1].substr(textPaths[tile - '0' - 1].length() - 10) << endl;
				out.close();
				//if (textPaths[tile - '0' - 1].substr(textPaths[tile - '0' - 1].length() - 10)=="Kimkoh.png") {
					boss = new Kimkoh();
					boss->setMap(map);
					boss->init("images/Chars/Kimkoh.png", glm::ivec2(140, 100), shaderProgram);
				//}
				/*else {
					enemies.push_back(new Enemy());
					enemies.back()->init(textPaths[tile - '0' - 1], glm::ivec2(blockS*j, 0), shaderProgram);
					enemies.back()->setMap(map);
				}*/
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

void EnemyManager::update(int deltaTime)
{
	
	list<Player*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->update(deltaTime);
	}
	if (boss != NULL)
		boss->update(deltaTime);
	
}

void EnemyManager::render()
{
	list<Player*>::iterator it;
	for (it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->render();	
	}
	if (boss != NULL)
		boss->render();
}
