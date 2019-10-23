#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Level* Level::loadLevel(const glm::vec2& minCoords, ShaderProgram& program) 
{

	Level* map = new Level(minCoords, program);

	return map;
}

Level::~Level()
{
	front->~TileMap();
	collision->~CollisionMap();
	back->~TileMap();
	background->~Sprite();
}

Level::Level(const glm::vec2& minCoords, ShaderProgram& program)
{
	pathToLevelFile = "levels/test04.txt";
	loadMapData();
	loadLayers(minCoords, program);
}

void Level::loadMapData() {
	//carrego variables de nivell
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;

	fin.open(pathToLevelFile.c_str());
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
	sstream >> pathToBackground;
	getline(fin, line);
	sstream.str(line);
	sstream >> pathToCollisionMap;
	fin.close();
}

void Level::loadLayers(const glm::vec2& minCoords, ShaderProgram& program)
{
	//Carrego layers
	Texture* backText = new Texture();
	backText->loadFromFile(pathToBackground, TEXTURE_PIXEL_FORMAT_RGB);
	
	/*Debug
	ofstream out;
	out.open("myDebug/testLayers.txt");
	out << mapSize.x << "<-MapSize.x BlockSize->" << blockSize << endl << mapSize.y << "<-MapSize.y BlockSize->" << blockSize;
	out.close();
	endOfDbug */
	background = Sprite::createSprite(glm::vec2(mapSize.x * blockSize, mapSize.y * blockSize),
		glm::vec2(1.0f, 1.0f), backText, &program);
	background->setNumberAnimations(0);
		
	front = TileMap::createTileMap(pathToLevelFile, "1", minCoords, program);
	back = TileMap::createTileMap(pathToLevelFile, "2", minCoords, program);

	collision = CollisionMap::loadCollisionMap(pathToCollisionMap, minCoords, 
		glm::ivec2(mapSize.x * blockSize, mapSize.y * blockSize));
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

void Level::render() const
{
	front->render();
	back->render();
	background->render();
}

void Level::free()
{
	background->free();
	back->render();
	front->free();
}