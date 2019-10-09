#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "TileMap.h"
class Level {
public:
	static Level* loadLevel(const string& levelName, const glm::vec2& minCoords, ShaderProgram& program);
	~Level();

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;

	void render() const;
	void free();

	int getTileSize() const { return layer1->getTileSize(); }

private:
	Level(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

	void loadLayers(const glm::vec2& minCoords, ShaderProgram& program);

private:

	//Layer 1 is front layer
	TileMap* layer1;
	//Layer 2 is player layer, it contains collisions.
	TileMap* layer2;
	//Layer 3 is background layer.
	TileMap* layer3;

	string path;
};
#endif // _LEVEL_INCLUDE
