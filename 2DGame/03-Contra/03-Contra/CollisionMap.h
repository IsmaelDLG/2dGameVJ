#ifndef _COLLISION_MAP_INCLUDE
#define _COLLISION_MAP_INCLUDE

#include "Texture.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class CollisionMap
{
public:
	static CollisionMap* loadCollisionMap(const string& path, const glm::ivec2& mapSize);
	~CollisionMap();
	
	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;

	bool damageCollision(const glm::ivec2& pos, const glm::ivec2& size) const;

	bool endOfLevel(const glm::ivec2& pos, const glm::ivec2& size);
private:
	CollisionMap(const string& path, const glm::ivec2& mapSize);

private:
	Texture* textMap;
	glm::ivec2 displaySize;
};

#endif //_COLLISION_MAP_INCLUDE 