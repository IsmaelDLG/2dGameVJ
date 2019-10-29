#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Level.h"
#include "Player.h"
#include "Bullet.h"
#include "SpredGunAmmo.h"
#include "EnemyManager.h"
#include <list>

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
	bool menu, begin, endStageOne, endStageTwo, endGame;
	Sprite* menuScreen;
	Sprite* button;
	Sprite* vides;

	Level *map;
	Player *player;
	Bullet* bullet;
	Bullet* bulletB;
	SpredGunAmmo* ammo;
	EnemyManager* enemyCtrl;
	ShaderProgram texProgram;
	float currentTime;
	int cameraVx, cameraVy;
	int deaths, playerReload;
	float cameraX, cameraY;
	float offsetMaxX, offsetMaxY, offsetMinX, offsetMinY, offsetMaxXBoss;
	list <Bullet*> bullets;
	list <Bullet*> bulletsBoss;
	glm::vec2 playerPos;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE
