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
	layer1.~TileMap();
	layer2.~TileMap();
	layer3.~TileMap();
}



Level::Level(const string& levelName, const glm::vec2& minCoords, ShaderProgram& program)
{
	path = "images/" + levelName + ".txt";
	layer1.createTileMap()
	try
	{
		loadLayers(3);
	}
	catch (const char* msh)
	{
		cout << msh << endl;
	}
	prepareArrays(minCoords, program);
}

void Level::loadLayers(unsigned int layer)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(path.c_str());
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
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	//Load different layers
	getline(fin, line);
	while (line.compare(0, 3, "END"))
	{
		layer1 = TileMap::createTileMap();
		layer1->loadLevel(fin);

	}
		
	fin.close();
}


void Level::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
}

bool Level::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	return false;
}

bool Level::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	return false;
}

bool Level::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	return false;
}

void Level::render() const
{
}

void Level::free()
{
}