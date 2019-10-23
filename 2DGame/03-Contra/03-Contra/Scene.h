#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "Player.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.
#define CAMERA_WIDTH 512
#define CAMERA_HEIGHT 512

class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	Level *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	float cameraVx, cameraVy;
	float cameraX, cameraY;
	float offsetMaxX, offsetMaxY, offsetMinX, offsetMinY;
	glm::vec2 playerPos;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

