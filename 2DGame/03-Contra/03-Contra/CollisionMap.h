#ifndef _COLLISION_MAP_INCLUDE
#define _COLLISION_MAP_INCLUDE

#include "Texture.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class CollisionMap
{
public:
	static CollisionMap* loadCollisionMap(const string& path, const glm::vec2& minCoords, ShaderProgram& program);
	~CollisionMap();
	
	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;

private:
	CollisionMap(const string& path);

private:
	Texture* textMap;
};

#endif //_COLLISION_MAP_INCLUDE