#include "CollisionMap.h"
#include <cstddef>
using namespace std;

#define MAX_COLLISION 64*3


CollisionMap* CollisionMap::loadCollisionMap(const string& path, const glm::vec2& minCoords, ShaderProgram& program)
{
	CollisionMap* map = new CollisionMap(path);
	return map;
}

CollisionMap::CollisionMap(const string& path) {
	textMap = new Texture();
	textMap->loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGB);
	
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
	
	x0 = pos.x;
	x1 = (pos.x + size.x - 1);
	y = (pos.y + size.y - 1);

	for(int x=x0; x<=x1; x++)
		{
			if((textMap->getPixel(x,y)).getAlpha() > MAX_COLLISION )
			{
				if(*posY - y + size.y <= 5)
				{
					*posY = y - size.y;
					return true;
				}
			}
		}
	
	return false;
}

