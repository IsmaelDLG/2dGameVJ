#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 16*2
#define SCREEN_Y 16*2

#define INIT_PLAYER_X_TILES 13
#define INIT_PLAYER_Y_TILES 1

Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	map = Level::loadLevel(glm::vec2(0.f, 0.f), texProgram);
	player = new Player();
	player->init(glm::ivec2(0.f, 0.f), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

	player->setMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	ammo = new SpredGunAmmo();
	ammo->init(glm::ivec2(0.f, 0.f), texProgram, player);
	ammo->setPosition(glm::vec2(30 * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

	ammo->setMap(map);

	playerPos = player->getPlayerPos();
	offsetMaxX = (map->getTileSize() * map->getMapsize().x) - CAMERA_WIDTH;
	offsetMaxY = (map->getTileSize() * map->getMapsize().y) - CAMERA_HEIGHT;
	offsetMinX = 0;
	offsetMinY = 0;
	deaths = 0;
	playerReload = 8;

	cameraX = (playerPos.x) - (CAMERA_WIDTH / 2);
	cameraY = (playerPos.y) - (CAMERA_HEIGHT / 2);
	if (cameraX > offsetMaxX) cameraX = offsetMaxX;
	else if (cameraX < offsetMinX) cameraX = offsetMinX;
	if (cameraY > offsetMaxY) cameraY = offsetMaxY;
	else if (cameraY < offsetMinY) cameraY = offsetMinY;

	projection = glm::translate(projection, glm::vec3(-cameraX, -cameraY, 0.f));

	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	if (!ammo->isPickedUp())
		ammo->update(deltaTime);
	if (deaths <= 4) {
		if (player->isDead()) {
			player->init(glm::ivec2(0.f, 0.f), texProgram);
			player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
			player->setMap(map);
			player->setState(false);
			deaths++;
		}
		else {
			playerPos = player->getPlayerPos();
			currentTime += deltaTime;
			player->update(deltaTime);
			if (player->getPlayerPos().x < offsetMinX) {
				glm::vec2 posRestri(offsetMinX, player->getPlayerPos().y);
				player->setPosition(posRestri);
			}

			if ((player->getPlayerPos().x - playerPos.x != 0) || (player->getPlayerPos().y - playerPos.y != 0)) {
				playerPos = player->getPlayerPos();
				projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
				cameraX = (playerPos.x) - (CAMERA_WIDTH / 3);
				cameraY = (playerPos.y) - (CAMERA_HEIGHT / 2);
				if (cameraX > offsetMaxX) cameraX = offsetMaxX;
				else if (cameraX < offsetMinX) cameraX = offsetMinX;
				if (cameraY > offsetMaxY) cameraY = offsetMaxY;
				else if (cameraY < offsetMinY) cameraY = offsetMinY;
				offsetMinX = cameraX;
			}
			else {
				cameraX = 0.f;
				cameraY = 0.f;
			}
			projection = glm::translate(projection, glm::vec3(-cameraX, -cameraY, 0.f));
			if (player->getisFiring()) {
				glm::vec2 position = player->getFirePoint();
				if (playerReload == 0){
					if (player->spreadGunOn()) {
						if (player->getdirection().y != 0) {
							bullet = new Bullet();
							bullet->init(glm::ivec2(0.f, 0.f), texProgram);
							bullet->setPosition(glm::vec2(position.x, position.y));
							glm::vec2 otherDirection = player->getdirection();
							bullet->setDirection(glm::vec2(1, 0));
							bullet->setMap(map);
							bullets.push_back(bullet);
							player->setFiring(false);

							bullet = new Bullet();
							bullet->init(glm::ivec2(0.f, 0.f), texProgram);
							bullet->setPosition(glm::vec2(position.x, position.y));
							bullet->setDirection(glm::vec2(0, otherDirection.y));
							bullet->setMap(map);
							bullets.push_back(bullet);
							player->setFiring(false);
						}
						else {
							bullet = new Bullet();
							bullet->init(glm::ivec2(0.f, 0.f), texProgram);
							bullet->setPosition(glm::vec2(position.x, position.y));
							glm::vec2 otherDirection = player->getdirection();
							bullet->setDirection(glm::vec2(otherDirection.x, otherDirection.y + 1));
							bullet->setMap(map);
							bullets.push_back(bullet);
							player->setFiring(false);

							bullet = new Bullet();
							bullet->init(glm::ivec2(0.f, 0.f), texProgram);
							bullet->setPosition(glm::vec2(position.x, position.y));
							bullet->setDirection(glm::vec2(otherDirection.x, otherDirection.y - 1));
							bullet->setMap(map);
							bullets.push_back(bullet);
							player->setFiring(false);
						}
					}
					bullet = new Bullet();
					bullet->init(glm::ivec2(0.f, 0.f), texProgram);
					bullet->setPosition(glm::vec2(position.x, position.y));
					bullet->setDirection(player->getdirection());
					bullet->setMap(map);
					bullets.push_back(bullet);
					player->setFiring(false);
					playerReload = 8;
				}
				else {
					--playerReload;
				}
				
			}
			if (!bullets.empty()) {
				for (int i = 0; i < bullets.size(); i++) {
					bullets[i]->update(deltaTime);
				}
			}
		}
	}
	else {
		cout << "gameOver" << endl;
	}
	
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	if (!ammo->isPickedUp())
		ammo->render();
	if (deaths <=4)
		player->render();
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->render();
		}
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



