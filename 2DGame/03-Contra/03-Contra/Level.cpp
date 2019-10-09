#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Level* Level::loadLevel(const string& levelName, const glm::vec2& minCoords, ShaderProgram& program) 
{
	Level* map = new Level(levelName, minCoords, program);

	return map;
}

Level::~Level()
{
	layer1->~TileMap();
	layer2->~TileMap();
	layer3->~TileMap();
}

Level::Level(const string& levelName, const glm::vec2& minCoords, ShaderProgram& program)
{
	path = "images/" + levelName + ".txt";
	
	try
	{
		loadLayers();
	}
	catch (const char* msh)
	{
		cout << msh << endl;
	}
}

void Level::loadLayers()
{

	//Carrego layers
	{
		//carregar totes les capes
		layer1 = TileMap::createTileMap(path, 1);

		layer2 = TileMap::createTileMap(path, 2);

		layer3 = TileMap::createTileMap(path, 3);
	}
}

bool Level::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	return layer2->collisionMoveLeft(pos,size);
}

bool Level::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	return layer2->collisionMoveRight(pos, size);
}

bool Level::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	return layer2->collisionMoveDown(pos, size, posY);
}

void Level::render() const
{
	layer3->render();
	layer2->render();
	//pendent d'arreglar
	layer1->render();
}

void Level::free()
{
	layer3->free();
	layer2->free();
	//pendent d'arreglar
	layer1->free();
}