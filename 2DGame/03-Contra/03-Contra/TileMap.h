#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string& file, unsigned int layer);
	void loadMap(const string& image, unsigned int layer);
	~TileMap();

	void render() const;
	void free();
	int getTileSize();
	
	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	
private:
	
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);


private:
	
	GLuint vao;
	GLuint vbo;
	glm::ivec2 mapSize;
	int tileSize, blockSize;
	GLint posLocation, texCoordLocation;
	glm::vec2 tileTexSize, tilesheetSize;
	Texture tilesheet;
	int *map;

};


#endif // _TILE_MAP_INCLUDE


