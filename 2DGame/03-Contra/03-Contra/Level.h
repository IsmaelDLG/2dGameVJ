#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "TileMap.h"
#include "Sprite.h"
#include "Texture.h"
#include "CollisionMap.h"

class Level {
public:
	static Level* loadLevel(const glm::vec2& minCoords, ShaderProgram& program);
	~Level();

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;


	void loadMapData();
	void render() const;
	void free();


	int getTileSize() const { return tileSize; }
	glm::vec2 getMapsize() const { return mapSize; }

private:
	Level(const glm::vec2& minCoords, ShaderProgram& program);

	void loadLayers(const glm::vec2& minCoords, ShaderProgram& program);

private:
	glm::ivec2 mapSize;
	int tileSize, blockSize;

	//Layer 1 is front layer
	TileMap* front;
	//Layer 2 is player layer, it contains collisions.
	CollisionMap* collision;
	//Layer 3 is background layer.
	TileMap* back;
	Sprite* background;

	string pathToLevelFile, pathToBackground, pathToCollisionMap;
};
#endif // _LEVEL_INCLUDE
