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
	menu = false;
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
	if (menu) {

	}
	else {
		map = Level::loadLevel(glm::vec2(0.f, 0.f), texProgram);
		player = new Player();
		player->init("images/Chars/Contra_PC_Spritesheet_Full.png", glm::ivec2(0.f, 0.f), texProgram);
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

		player->setMap(map);

		enemyCtrl = new EnemyManager();
		enemyCtrl->init(map, texProgram);

		projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

		playerPos = player->getPlayerPos();
		offsetMaxX = (map->getTileSize() * map->getMapsize().x) - CAMERA_WIDTH;
		offsetMaxY = (map->getTileSize() * map->getMapsize().y) - CAMERA_HEIGHT;
		offsetMinX = 0;
		offsetMinY = 0;

		cameraX = (playerPos.x) - (CAMERA_WIDTH / 2);
		cameraY = (playerPos.y) - (CAMERA_HEIGHT / 2);
		if (cameraX > offsetMaxX) cameraX = offsetMaxX;
		else if (cameraX < offsetMinX) cameraX = offsetMinX;
		if (cameraY > offsetMaxY) cameraY = offsetMaxY;
		else if (cameraY < offsetMinY) cameraY = offsetMinY;

		projection = glm::translate(projection, glm::vec3(-cameraX, -cameraY, 0.f));

		currentTime = 0.0f;
	}
	
}

void Scene::update(int deltaTime)
{
	if (menu) {

	}
	else {
		playerPos = player->getPlayerPos();
		currentTime += deltaTime;
		player->update(deltaTime);
		enemyCtrl->update(deltaTime);


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
	}
	
}

void Scene::render()
{
	if (menu) {

	}
	else {
		glm::mat4 modelview;
		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		modelview = glm::mat4(1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
		map->render();
		player->render();
		enemyCtrl->render();
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



