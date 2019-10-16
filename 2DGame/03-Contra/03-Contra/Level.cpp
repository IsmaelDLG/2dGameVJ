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
	foreground->~TileMap();
	collision->~TileMap();
	background1->~TileMap();
	//no se si backgrround2 ha de fer algo
	background2->~Sprite();
}

Level::Level(const string& levelName, const glm::vec2& minCoords, ShaderProgram& program)
{
	pathToTileMap = "levels/" + levelName + ".txt";
	
	loadLayers(minCoords, program);

}

void Level::loadLayers(const glm::vec2& minCoords, ShaderProgram& program)
{
	//carrego variables de nivell
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;

	fin.open(pathToTileMap.c_str());
	if (!fin.is_open())
		throw "Couldn't open file!";
	getline(fin, line);
	if (line.compare(0, 5, "LEVEL") != 0)
		throw "Not a level file!";
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> pathToBackground2;
	fin.close();
	
	//Carrego layers
	{
		//glm::vec2 coordZero = glm::vec2(0.0f, 0.0f);

		//carregar totes les capes
		backText2 = new Texture();
		backText2->loadFromFile(pathToBackground2, TEXTURE_PIXEL_FORMAT_RGB);
		background2 = Sprite::createSprite(glm::vec2(mapSize.x * blockSize, mapSize.y * blockSize), glm::vec2(1.0f, 1.0f), backText2, &program);
		//La resta de capes es renderitzen minCoords més enllà, idkwhy.
		
		foreground = TileMap::createTileMap(pathToTileMap, "1", minCoords, program);

		collision = TileMap::createTileMap(pathToTileMap, "2", minCoords, program);

		background1 = TileMap::createTileMap(pathToTileMap, "3", minCoords, program);
	}
}

bool Level::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	return collision->collisionMoveLeft(pos,size);
}

bool Level::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	return collision->collisionMoveRight(pos, size);
}

bool Level::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	return collision->collisionMoveDown(pos, size, posY);
}

void Level::renderLayers() const
{
	//pendent d'arreglar	texProgram.setUniformMatrix4f("modelview", modelview);
	background1->render();
	collision->render();
	foreground->render();
}

void Level::renderBackground2() const
{
	background2->render();
}

void Level::free()
{
	//no se si ha de fer algo la back2
	background2->free();
	//pendent d'arreglar
	background1->render();
	collision->free();
	foreground->free();
}