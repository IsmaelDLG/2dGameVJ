#include <cmath>
#include <iostream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4 
#define JUMP_HEIGHT 72
#define FALL_STEP 3
#define P_SIZE 48


enum PlayerAnims
{
	STAND_RIGHT, MOVE_RIGHT, JUMPING_RIGHT, LAY_RIGHT, LAY_RIGHT_SHOOTING, MOVE_RIGHT_SHOOTING, STAND_RIGHT_SHOOTING,
	DYING, STAND_LEFT, MOVE_LEFT, JUMPING_LEFT, LAY_LEFT, LAY_LEFT_SHOOTING, MOVE_LEFT_SHOOTING, STAND_LEFT_SHOOTING,
};


void Player::init(const string& path, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	onTheAir = false;
	spraygun = false;
	goingRight = true;
	spritesheet.loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(P_SIZE, P_SIZE), glm::vec2(0.125, 0.0625), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(15);

		/* LEFT ANIMATIONS*/
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.875f, 0.5625f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.875f, 0.625f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.750f, 0.625f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.625f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.500f, 0.625f));

		sprite->setAnimationSpeed(JUMPING_LEFT, 8);
		sprite->addKeyframe(JUMPING_LEFT, glm::vec2(0.375f, 0.5f));
		sprite->addKeyframe(JUMPING_LEFT, glm::vec2(0.250f, 0.5f));
		sprite->addKeyframe(JUMPING_LEFT, glm::vec2(0.125f, 0.5f));
		sprite->addKeyframe(JUMPING_LEFT, glm::vec2(0.f, 0.5f));

		sprite->setAnimationSpeed(LAY_LEFT, 8);
		sprite->addKeyframe(LAY_LEFT, glm::vec2(0.875f, 0.5f));

		sprite->setAnimationSpeed(LAY_LEFT_SHOOTING, 8);
		sprite->addKeyframe(LAY_LEFT_SHOOTING, glm::vec2(0.750f, 0.5f));
		sprite->addKeyframe(LAY_LEFT_SHOOTING, glm::vec2(0.625f, 0.5f));

		sprite->setAnimationSpeed(MOVE_LEFT_SHOOTING, 8);
		sprite->addKeyframe(MOVE_LEFT_SHOOTING, glm::vec2(0.500f, 0.5625f));
		sprite->addKeyframe(MOVE_LEFT_SHOOTING, glm::vec2(0.750f, 0.625f));
		sprite->addKeyframe(MOVE_LEFT_SHOOTING, glm::vec2(0.250f, 0.5625f));
		sprite->addKeyframe(MOVE_LEFT_SHOOTING, glm::vec2(0.500f, 0.625f));

		sprite->setAnimationSpeed(STAND_LEFT_SHOOTING, 8);
		sprite->addKeyframe(STAND_LEFT_SHOOTING, glm::vec2(0.750f, 0.5625f));
		sprite->addKeyframe(STAND_LEFT_SHOOTING, glm::vec2(0.625f, 0.5625f));

		/* RIGHT ANIMATIONS*/

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.0625f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.125f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.250f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.375f, 0.125f));

		sprite->setAnimationSpeed(JUMPING_RIGHT, 8);
		sprite->addKeyframe(JUMPING_RIGHT, glm::vec2(0.500f, 0.f));
		sprite->addKeyframe(JUMPING_RIGHT, glm::vec2(0.625f, 0.f));
		sprite->addKeyframe(JUMPING_RIGHT, glm::vec2(0.750f, 0.f));
		sprite->addKeyframe(JUMPING_RIGHT, glm::vec2(0.875f, 0.f));

		sprite->setAnimationSpeed(LAY_RIGHT, 8);
		sprite->addKeyframe(LAY_RIGHT, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(LAY_RIGHT_SHOOTING, 8);
		sprite->addKeyframe(LAY_RIGHT_SHOOTING, glm::vec2(0.125f, 0.f));
		sprite->addKeyframe(LAY_RIGHT_SHOOTING, glm::vec2(0.250f, 0.f));

		sprite->setAnimationSpeed(MOVE_RIGHT_SHOOTING, 8);
		sprite->addKeyframe(MOVE_RIGHT_SHOOTING, glm::vec2(0.375f, 0.0625f));
		sprite->addKeyframe(MOVE_RIGHT_SHOOTING, glm::vec2(0.125f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT_SHOOTING, glm::vec2(0.625f, 0.0625f));
		sprite->addKeyframe(MOVE_RIGHT_SHOOTING, glm::vec2(0.375f, 0.125f));

		sprite->setAnimationSpeed(STAND_RIGHT_SHOOTING, 8);
		sprite->addKeyframe(STAND_RIGHT_SHOOTING, glm::vec2(0.125f, 0.0625f));
		sprite->addKeyframe(STAND_RIGHT_SHOOTING, glm::vec2(0.250f, 0.0625f));

		//sprite->setAnimationSpeed(DYING, 8);
		
	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		goingRight = false;
		if (!onTheAir) {
			if (Game::instance().getKey(32)) {
				if (sprite->animation() != MOVE_LEFT_SHOOTING)
					sprite->changeAnimation(MOVE_LEFT_SHOOTING);
			}
			else {
				if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
			}
		}
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(P_SIZE, P_SIZE),&posPlayer.y)) {
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		goingRight = true;
		if (!onTheAir) {
			if (Game::instance().getKey(32)) {
				if (sprite->animation() != MOVE_RIGHT_SHOOTING)
					sprite->changeAnimation(MOVE_RIGHT_SHOOTING);
			}
			else {
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
			}
		}
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(P_SIZE, P_SIZE), &posPlayer.y))
		{
			posPlayer.x -= 2 ;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		if (!onTheAir) {
			if (Game::instance().getKey(32)) {
				if (goingRight && sprite->animation() != LAY_RIGHT_SHOOTING)
					sprite->changeAnimation(LAY_RIGHT_SHOOTING);
				else if (!goingRight && sprite->animation() != LAY_LEFT_SHOOTING)
					sprite->changeAnimation(LAY_LEFT_SHOOTING);
			}
			else {
				if (goingRight && sprite->animation() != LAY_RIGHT)
					sprite->changeAnimation(LAY_RIGHT);
				else if (!goingRight && sprite->animation() != LAY_LEFT)
					sprite->changeAnimation(LAY_LEFT);
			}
		}
	}
	else
	{
		if (Game::instance().getKey(32)) {
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == LAY_LEFT
				|| sprite->animation() == LAY_LEFT_SHOOTING || sprite->animation() == MOVE_LEFT_SHOOTING
				|| sprite->animation() == STAND_LEFT)
				sprite->changeAnimation(STAND_LEFT_SHOOTING);
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == LAY_RIGHT 
				|| sprite->animation() == LAY_RIGHT_SHOOTING || sprite->animation() == MOVE_RIGHT_SHOOTING 
				|| sprite->animation() == STAND_RIGHT)
				sprite->changeAnimation(STAND_RIGHT_SHOOTING);
		}
		else {
			if (sprite->animation() == MOVE_LEFT || sprite->animation() == LAY_LEFT
				|| sprite->animation() == STAND_LEFT_SHOOTING)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == LAY_RIGHT 
				|| sprite->animation() == STAND_RIGHT_SHOOTING)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (goingRight) {
			if (sprite->animation() != JUMPING_RIGHT)
				sprite->changeAnimation(JUMPING_RIGHT);
		}
		else {
			if (sprite->animation() != JUMPING_LEFT)
				sprite->changeAnimation(JUMPING_LEFT);
		}
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else {
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(P_SIZE, P_SIZE), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(P_SIZE, P_SIZE), &posPlayer.y))
		{
			onTheAir = false;
			if (goingRight) {
				if (sprite->animation() == JUMPING_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
			}
			else {
				if (sprite->animation() == JUMPING_LEFT)
					sprite->changeAnimation(STAND_LEFT);
			}
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				if(sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
					sprite->changeAnimation(JUMPING_RIGHT);
				else if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
					sprite->changeAnimation(JUMPING_LEFT);
				bJumping = true;
				onTheAir = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setMap(Level *myMap)
{
	map = myMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Player::min(int a, int b) {
	int ret;
	if (a <= b) ret = a;
	else ret = b;
	return ret;
}


