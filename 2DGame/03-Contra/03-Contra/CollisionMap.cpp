#include "CollisionMap.h"
//debug only
#include <fstream>
//debug only
using namespace std;

#define MAX_COLLISION 64*3


CollisionMap* CollisionMap::loadCollisionMap(const string& path, const glm::vec2& minCoords, const glm::ivec2& mapSize)
{
	CollisionMap* map = new CollisionMap(path, mapSize);
	return map;
}

CollisionMap::CollisionMap(const string& path, const glm::ivec2& mapSize) {
	textMap = new Texture();
	textMap->loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	displaySize = mapSize;
}

CollisionMap::~CollisionMap()
{
	if (textMap != NULL)
		delete textMap;
}

bool CollisionMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;
	
	x = pos.x;
	y0 = pos.y;
	y1 = pos.y + size.y - 1;

	for (int y = y0; y <= y1; y++)
	{
		if ((textMap->getPixel(x,y)).getAlpha() > 64*3 )
			return true;
	}

	return false;
}

bool CollisionMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;
	
	x = pos.x;
	y0 = pos.y;
	y1 = pos.y + size.y - 1;

	for (int y = y0; y <= y1; y++)
	{
		if ((textMap->getPixel(x,y)).getAlpha() > 64*3 )
			return true;
	}

	return false;}

bool CollisionMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	return false;
}

bool CollisionMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{	
	int x0, x1, y;
	float factorX, factorY;
	
	x0 = pos.x;
	x1 = (pos.x + size.x - 1);
	y = (pos.y + size.y - 1);


	factorX = ((textMap->width()*1.0f) / (displaySize.x*1.0f));
	factorY = ((textMap->height()*1.0f) / (displaySize.y*1.0f));
	/*//Debug
	ofstream out;
	out.open("myDebug/testCollision.txt", ios::app);
	out << "textSize: " << textMap->width() << " " << textMap->height() << endl;
	out << "dispSize: " << displaySize.x << " " << displaySize.y << endl;
	out << "Factors: "<< factorX << " " << factorY << endl;
	out.close();
	//devug end*/
	for(int x=x0; x<=x1; x++)
	{
		if((textMap->getPixel(int(x * factorX), int(y * factorY)).getAlpha() > MAX_COLLISION) &&
			((textMap->getPixel(int(x * factorX), int(y * factorY))).getBlack() > MAX_COLLISION ))
		{
			if(*posY - y + size.y <= 4)
			{
				*posY = y - size.y - 4;
				/*//Debug
				ofstream out;
				out.open("myDebug/testCollision.txt", ios::app);
				out << "( " << x << ", " << y << ") Collision returns true. Black is: ";
				out << (textMap->getPixel(int(x*factorX), int(y*factorY))).getBlack(); 
				out << " Alpha is: ";
				out << (textMap->getPixel(int(x*factorX), int(y*factorY))).getAlpha();
				out << endl;
				out.close();
				//Debug*/
				return true;
				}
			}
	}
	/*
	//Debug
	out.open("myDebug/testCollision.txt", ios::app);
	out << "(" << int(x0*factorX) << ", " << int(y*factorY) << ") Collision returns false.";
	out << endl;
	out.close();
	//Debug
	*/
	return false;
}

