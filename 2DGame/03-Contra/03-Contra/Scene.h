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
#include <irrKlang.h>
using namespace irrklang;

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
	bool menu, begin, endStageOne, endStageTwo, endGame, gameOver;
	Sprite* menuScreen;
	Sprite* button;
	Sprite* vides;
	ISoundEngine* engine;
	Level *map;
	Player *player;
	Bullet* bullet;
	Bullet* bulletB;
	SpredGunAmmo* ammo;
	EnemyManager* enemyCtrl;
	ShaderProgram texProgram;
	float currentTime;
	int cameraVx, cameraVy;
	int deaths, playerReload, bossReload;
	float cameraX, cameraY;
	float offsetMaxX, offsetMaxY, offsetMinX, offsetMinY, offsetMaxXBoss;
	list <Bullet*> bullets;
	list <Bullet*> bulletsBoss;
	glm::vec2 playerPos;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE
