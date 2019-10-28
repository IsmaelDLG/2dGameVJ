#include "CollisionMap.h"
//debug only
#include <fstream>
//debug only
using namespace std;

#define MAX_COLLISION 64*3


CollisionMap* CollisionMap::loadCollisionMap(const string& path, const glm::ivec2& mapSize)
{
	CollisionMap* map = new CollisionMap(path, mapSize);
	return map;
}

CollisionMap::CollisionMap(const string& path, const glm::ivec2& mapSize) {
	textMap = new Texture();
	textMap->loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	//esto està hardcoded?
	displaySize = mapSize;
}

CollisionMap::~CollisionMap()
{
	if (textMap != NULL)
		delete textMap;
}

bool CollisionMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	
	int x, y0, y1;
	float factorX, factorY;

	x = pos.x;
	y0 = pos.y + size.y - 1 - int(size.y/10.0f);
	y1 = pos.y;

	factorX = ((textMap->width() * 1.0f) / (displaySize.x * 1.0f));
	factorY = ((textMap->height() * 1.0f) / (displaySize.y * 1.0f));

	for (int y = y0; y >= y1; y--)
	{
		if ((textMap->getPixel(int(x * factorX), int(y * factorY)).getAlpha() > MAX_COLLISION) &&
			((textMap->getPixel(int(x * factorX), int(y * factorY))).getBlack() == 0) /*el black retorna 0*/)
		{
			return true;
		}
	}
	return false;
}

bool CollisionMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x, y0, y1;
	float factorX, factorY;

	x = pos.x + size.x + 1;
	y0 = pos.y + size.y - 1 - int(size.y/10.f);
	y1 = pos.y;

	factorX = ((textMap->width() * 1.0f) / (displaySize.x * 1.0f));
	factorY = ((textMap->height() * 1.0f) / (displaySize.y * 1.0f));
	
	for (int y = y0; y > y1; y--)
	{
		if ((textMap->getPixel(int(x * factorX), int(y * factorY)).getAlpha() > MAX_COLLISION) &&
			((textMap->getPixel(int(x * factorX), int(y * factorY))).getBlack() == 0) /*el black retorna 0*/)
		{
			return true;
		}
	}
	return false;
}

bool CollisionMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	return false;
}

bool CollisionMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{	
	int x0, x1, y;
	float factorX, factorY;
	
	x0 = pos.x ;
	x1 = (pos.x + size.x - 1);
	y = (pos.y + size.y - 1);

	factorX = ((textMap->width()*1.0f) / (displaySize.x*1.0f));
	factorY = ((textMap->height()*1.0f) / (displaySize.y*1.0f));

	for (int x = x0; x <= x1; x++)
	{
		if ((textMap->getPixel(int(x * factorX), int(y * factorY)).getAlpha() > MAX_COLLISION) && (
			((textMap->getPixel(int(x * factorX), int(y * factorY))).getBlack() == 0 /*el black retorna 0 si es 100%*/) ||
			((textMap->getPixel(int(x * factorX), int(y * factorY))).getBlue() >= MAX_COLLISION )))
		{
			*posY = y - size.y - 3;
			return true;
		}
	}
	return false;
}

bool CollisionMap::endOfLevel(const glm::ivec2& pos, const glm::ivec2& size)
{
	int x0, x1, y;
	float factorX, factorY;

	x0 = pos.x;
	x1 = (pos.x + size.x - 1);
	y = (pos.y + size.y - 1);

	factorX = ((textMap->width() * 1.0f) / (displaySize.x * 1.0f));
	factorY = ((textMap->height() * 1.0f) / (displaySize.y * 1.0f));


	for (int x = x0; x <= x1; x++)
	{
		if ((textMap->getPixel(int(x * factorX), int(y * factorY)).getAlpha() > MAX_COLLISION) &&
			((textMap->getPixel(int(x * factorX), int(y * factorY))).getGreen() == 255))
		{
			return true;
		}
	}

	return false;
}

