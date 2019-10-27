#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "Player.h"
#include "Bullet.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.
#define CAMERA_WIDTH 256
#define CAMERA_HEIGHT 256

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
	Bullet* bullet;
	ShaderProgram texProgram;
	float currentTime;
	int cameraVx, cameraVy;
	int deaths, playerReload;
	float cameraX, cameraY;
	float offsetMaxX, offsetMaxY, offsetMinX, offsetMinY;
	vector <Bullet*> bullets;
	glm::vec2 playerPos;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

