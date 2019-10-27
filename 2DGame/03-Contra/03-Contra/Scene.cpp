#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

//debug
#include <fstream>

#define SCREEN_X 16*2
#define SCREEN_Y 16*2

#define INIT_PLAYER_X_TILES 13
#define INIT_PLAYER_Y_TILES 1

enum PlayerAnims
{
	FADE
};


Scene::Scene()
{
	map = NULL;
	player = NULL;
	menuScreen = NULL;
	button = NULL;
	enemyCtrl = NULL;
	menu = true;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;

	if (menuScreen != NULL)
		delete menuScreen;
	/*
	if (button != NULL)
		delete button;
		*/
	/*
	if (enemyCtrl != NULL)
		delete enemyCtrl;*/
}


void Scene::init()
{
	initShaders();
	cameraX = 0;
	cameraY = 0;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	
	if (menu) {
		if (/*stage_one*/false) {

		}
		else if (/*stage_two*/false) {

		}
		else if (/*stage_three*/false) {

		}
		else /*menu_inicial*/ {

			Texture* menuTex = new Texture();
			menuTex->loadFromFile("images/Menus/StartMenu.png", TEXTURE_PIXEL_FORMAT_RGB);
			menuScreen = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT),
				glm::vec2(1.0f, 1.0f), menuTex, &texProgram);
			menuScreen->setNumberAnimations(0);

			//Text que parpadeja
			Texture* startTex = new Texture();
			startTex->loadFromFile("images/Menus/StartButton.png", TEXTURE_PIXEL_FORMAT_RGBA);
			button = Sprite::createSprite(glm::vec2(startTex->width() / 4 * 2.5, startTex->height() * 1.5),
				glm::vec2(0.25f, 1.f), startTex, &texProgram);
			button->setNumberAnimations(1);
			button->setPosition(glm::vec2(SCREEN_WIDTH / 4 + 12, SCREEN_HEIGHT * 3 / 4));
			/*Fading animation*/
			button->setAnimationSpeed(FADE, 6);
			button->addKeyframe(FADE, glm::vec2(0.f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.25f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.50f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.75f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.75f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.50f, 0.f));
			button->addKeyframe(FADE, glm::vec2(0.25f, 0.f));

			//Començo l'animació
			button->changeAnimation(0);
		}
		}
	else {
		map = Level::loadLevel(glm::vec2(20.f, 0.f), texProgram);
		player = new Player();
		player->init("images/Chars/Contra_PC_Spritesheet_Full.png", glm::ivec2(0.f, 0.f), texProgram);
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

		player->setMap(map);
    
		ammo = new SpredGunAmmo();
		ammo->init(glm::ivec2(0.f, 0.f), texProgram, player);
		ammo->setPosition(glm::vec2(30 * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

		ammo->setMap(map);
		deaths = 0;
		playerReload = 8;

		enemyCtrl = new EnemyManager();
		enemyCtrl->init(map, texProgram);

		playerPos = player->getPlayerPos();
		offsetMaxX = (map->getTileSize() * map->getMapsize().x) - CAMERA_WIDTH;
		offsetMinX = 0;

		cameraX = (playerPos.x) - (CAMERA_WIDTH / 2);
		if (cameraX > offsetMaxX) cameraX = offsetMaxX;
		else if (cameraX < offsetMinX) cameraX = offsetMinX;
		//La posicio en Y ha de ser fixa en el primer nivell
		cameraY = SCREEN_HEIGHT / 4 - 9 ;
		currentTime = 0.0f;
	}
	projection = glm::translate(projection, glm::vec3(-cameraX, -cameraY, 0.f));
}

void Scene::update(int deltaTime)
{
	if (menu) {
		if (/*stage_one*/false) {

		}
		else if (/*stage_two*/false) {

		}
		else if (/*stage_three*/false) {

		}
		else /*menu_inicial*/ {
			if (Game::instance().getKey(13)) {
				//this->~Scene();
				menu = false;
				//comencem a jugar
				this->init();
			}
			else {
				menuScreen->update(deltaTime);
				button->update(deltaTime);
			}
		}
	}
	else {
		if (player->isEndOfLevel()) {
			menu = true;
			//tornem a menu
			this->init();
			//estaria bé fer una anumació de victoria o algo
			//també spawnejar un bicho que diga completed o algo
		}
		else {
		  if (!ammo->isPickedUp()) ammo->update(deltaTime);
		  if (deaths != 4) {
			if (player->isDead()) {
			  player->init("images/Chars/Contra_PC_Spritesheet_Full.png", glm::ivec2(0.f, 0.f), texProgram);
			  player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
			  player->setMap(map);
			  player->setState(false);
			  deaths++;
			}
			else {
				playerPos = player->getPlayerPos();
				currentTime += deltaTime;
				player->update(deltaTime);
				enemyCtrl->update(deltaTime);
				cameraY = 0.f;

				if (player->getPlayerPos().x < offsetMinX) {
				  glm::vec2 posRestri(offsetMinX, player->getPlayerPos().y);
				  player->setPosition(posRestri);
				}

				if ((player->getPlayerPos().x - playerPos.x != 0) || (player->getPlayerPos().y - playerPos.y != 0)) {
				  playerPos = player->getPlayerPos();
				  projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
				  cameraX = (playerPos.x) - (CAMERA_WIDTH / 3);
				  //cameraY = (playerPos.y) - (CAMERA_HEIGHT / 2);
				  if (cameraX > offsetMaxX) cameraX = offsetMaxX;
				  else if (cameraX < offsetMinX) cameraX = offsetMinX;
				  //if (cameraY > offsetMaxY) cameraY = offsetMaxY;
				  //else if (cameraY < offsetMinY) cameraY = offsetMinY;
				  offsetMinX = cameraX;

				  projection = glm::translate(projection, glm::vec3(-cameraX, -SCREEN_HEIGHT/4 - 9, 0.f));
				}
				else {
				  cameraX = 0.f;
				  projection = glm::translate(projection, glm::vec3(-cameraX, 0, 0.f));
				}
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
					  glm::vec2 posB = bullets[i]->getBulletpos();
					  if(posB.x <= offsetMaxX && posB.x >= offsetMinX)
						bullets[i]->update(deltaTime);
					}
				  }
			}
		  }
		  else {
		  menu = true;
		  this->init();
		  }
		}
		//camera Y fixa
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
	if (menu) {
		if (/*stage_one*/false) {

		}
		else if (/*stage_two*/false) {

		}
		else if (/*stage_three*/false) {

		}
		else /*menu_inicial*/ {
			menuScreen->render();
			button->render();
		}
	}
	else {
		map->render();
		enemyCtrl->render();
		if (!ammo->isPickedUp()) ammo->render();
		if (deaths <=4) player->render();
		if (!bullets.empty()) {
		  for (int i = 0; i < bullets.size(); i++) {
			glm::vec2 posB = bullets[i]->getBulletpos();
			if (posB.x <= offsetMaxX && posB.x >= offsetMinX)
			  bullets[i]->render();
		  }
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



