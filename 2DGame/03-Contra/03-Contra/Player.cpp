#include <cmath>
#include <iostream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

#define JUMP_ANGLE_STEP 4 
#define JUMP_HEIGHT 72
#define FALL_STEP 4
#define P_SIZE 48


enum PlayerAnims
{
	STAND_RIGHT, MOVE_RIGHT, JUMPING_RIGHT, LAY_RIGHT, LAY_RIGHT_SHOOTING, MOVE_RIGHT_SHOOTING, STAND_RIGHT_SHOOTING,
	DYING, STAND_LEFT, MOVE_LEFT, JUMPING_LEFT, LAY_LEFT, LAY_LEFT_SHOOTING, MOVE_LEFT_SHOOTING, STAND_LEFT_SHOOTING,
	MOVE_LOOK_UP_RIGHT, MOVE_LOOK_DOWN_RIGHT, MOVE_LOOK_UP_LEFT, MOVE_LOOK_DOWN_LEFT, LOOK_DOWN_LEFT, LOOK_UP_LEFT,
	LOOK_DOWN_RIGHT, LOOK_UP_RIGHT
};


void Player::init(const string& path, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	onTheAir = false;
	spreadGun = false;;
	dead = false;
	goingRight = true;
	isFiring = false;
	direction = glm::vec2(1,0);
	health = 1;
	firePoint = glm::vec2(posPlayer.x + 51.f, posPlayer.y + 36.f);
	spritesheet = new Texture();
	spritesheet->loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(P_SIZE, P_SIZE), glm::vec2(0.125, 0.0625), spritesheet, &shaderProgram);
	sprite->setNumberAnimations(23);

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

		sprite->setAnimationSpeed(MOVE_LOOK_DOWN_LEFT, 8);
		sprite->addKeyframe(MOVE_LOOK_DOWN_LEFT, glm::vec2(0.875f, 0.75f));
		sprite->addKeyframe(MOVE_LOOK_DOWN_LEFT, glm::vec2(0.750f, 0.75f));
		sprite->addKeyframe(MOVE_LOOK_DOWN_LEFT, glm::vec2(0.625f, 0.75f));
		sprite->addKeyframe(MOVE_LOOK_DOWN_LEFT, glm::vec2(0.500f, 0.75f));

		sprite->setAnimationSpeed(MOVE_LOOK_UP_LEFT, 8);
		sprite->addKeyframe(MOVE_LOOK_UP_LEFT, glm::vec2(0.875f, 0.6875f));
		sprite->addKeyframe(MOVE_LOOK_UP_LEFT, glm::vec2(0.750f, 0.6875f));
		sprite->addKeyframe(MOVE_LOOK_UP_LEFT, glm::vec2(0.625f, 0.6875f));
		sprite->addKeyframe(MOVE_LOOK_UP_LEFT, glm::vec2(0.500f, 0.6875f));

		sprite->setAnimationSpeed(LOOK_DOWN_LEFT, 8);
		sprite->addKeyframe(LOOK_DOWN_LEFT, glm::vec2(0.750f, 0.75f));

		sprite->setAnimationSpeed(MOVE_LOOK_UP_LEFT, 8);
		sprite->addKeyframe(LOOK_UP_LEFT, glm::vec2(0.750f, 0.6875f));

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

		sprite->setAnimationSpeed(MOVE_LOOK_DOWN_RIGHT, 8);
		sprite->addKeyframe(MOVE_LOOK_DOWN_RIGHT, glm::vec2(0.0, 0.25f));
		sprite->addKeyframe(MOVE_LOOK_DOWN_RIGHT, glm::vec2(0.125f, 0.25f));
		sprite->addKeyframe(MOVE_LOOK_DOWN_RIGHT, glm::vec2(0.250f, 0.25f));
		sprite->addKeyframe(MOVE_LOOK_DOWN_RIGHT, glm::vec2(0.375f, 0.25f));

		sprite->setAnimationSpeed(MOVE_LOOK_UP_RIGHT, 8);
		sprite->addKeyframe(MOVE_LOOK_UP_RIGHT, glm::vec2(0.0, 0.1875f));
		sprite->addKeyframe(MOVE_LOOK_UP_RIGHT, glm::vec2(0.125f, 0.1875f));
		sprite->addKeyframe(MOVE_LOOK_UP_RIGHT, glm::vec2(0.250f, 0.1875f));
		sprite->addKeyframe(MOVE_LOOK_UP_RIGHT, glm::vec2(0.375f, 0.1875f));

		sprite->setAnimationSpeed(LOOK_DOWN_RIGHT, 8);
		sprite->addKeyframe(LOOK_DOWN_RIGHT, glm::vec2(0.125f, 0.25f));

		sprite->setAnimationSpeed(LOOK_UP_RIGHT, 8);
		sprite->addKeyframe(LOOK_UP_RIGHT, glm::vec2(0.125f, 0.1875f));

		sprite->setAnimationSpeed(DYING, 8);
		sprite->addKeyframe(DYING, glm::vec2(0.375f, 0.125f));
		sprite->addKeyframe(DYING, glm::vec2(0.3125f, 0.125f));
		
	sprite->changeAnimation(1);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	if (map->damages(sprite->getRealMinPos(glm::vec2(P_SIZE,P_SIZE),glm::vec2(0.f)), 
		sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0.f)))) {
		this->takeDamage(1);
	}
	sprite->update(deltaTime);
	if (!dead) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			goingRight = false;
			firePoint = glm::vec2(posPlayer.x + 14, posPlayer.y + 36);
			if (!onTheAir) {
				if (Game::instance().getKey(120)) {
					isFiring = true;
					direction = glm::vec2(-1, 0);
					if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
						if (sprite->animation() != MOVE_LOOK_DOWN_LEFT)
							sprite->changeAnimation(MOVE_LOOK_DOWN_LEFT);
						firePoint = glm::vec2(posPlayer.x + 9, posPlayer.y + 52);
						direction = glm::vec2(-1, 1);
					}
					else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
						if (sprite->animation() != MOVE_LOOK_UP_LEFT)
							sprite->changeAnimation(MOVE_LOOK_UP_LEFT);
						firePoint = glm::vec2(posPlayer.x + 17, posPlayer.y + 17);
						direction = glm::vec2(-1, -1);
					}
					else {
						if (sprite->animation() != MOVE_LEFT_SHOOTING)
							sprite->changeAnimation(MOVE_LEFT_SHOOTING);
					}
				}
				else {
					isFiring = false;
					if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
						if (sprite->animation() != MOVE_LOOK_DOWN_LEFT)
							sprite->changeAnimation(MOVE_LOOK_DOWN_LEFT);
						firePoint = glm::vec2(posPlayer.x + 9, posPlayer.y + 52);
					}
					else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
						if (sprite->animation() != MOVE_LOOK_UP_LEFT)
							sprite->changeAnimation(MOVE_LOOK_UP_LEFT);
						firePoint = glm::vec2(posPlayer.x + 17, posPlayer.y + 17);
					}
					else {
						if (sprite->animation() != MOVE_LEFT)
							sprite->changeAnimation(MOVE_LEFT);
					}
				}
			}
			posPlayer.x -= 2;
			if(map->collisionMoveLeft(sprite->getRealMinPos(glm::vec2(P_SIZE,P_SIZE),glm::vec2(-2,0)), 
			sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-2, 0)),&posPlayer.y)) {
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			goingRight = true;
			firePoint = glm::vec2(posPlayer.x + 51, posPlayer.y + 36);
			if (!onTheAir) {
				if (Game::instance().getKey(120)) {
					isFiring = true;
					direction = glm::vec2(1, 0);
					if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
						if (sprite->animation() != MOVE_LOOK_DOWN_RIGHT)
							sprite->changeAnimation(MOVE_LOOK_DOWN_RIGHT);
						firePoint = glm::vec2(posPlayer.x + 56, posPlayer.y + 52);
						direction = glm::vec2(1, 1);
					}
					else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
						if (sprite->animation() != MOVE_LOOK_UP_RIGHT)
							sprite->changeAnimation(MOVE_LOOK_UP_RIGHT);
						firePoint = glm::vec2(posPlayer.x + 48, posPlayer.y + 17);
						direction = glm::vec2(1, -1);
					}
					else {
						if (sprite->animation() != MOVE_RIGHT_SHOOTING)
							sprite->changeAnimation(MOVE_RIGHT_SHOOTING);
					}
				}
				else {
					isFiring = false;
					if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
						if (sprite->animation() != MOVE_LOOK_DOWN_RIGHT)
							sprite->changeAnimation(MOVE_LOOK_DOWN_RIGHT);
						firePoint = glm::vec2(posPlayer.x + 56, posPlayer.y + 52);
					}
					else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
						if (sprite->animation() != MOVE_LOOK_UP_RIGHT)
							sprite->changeAnimation(MOVE_LOOK_UP_RIGHT);
						firePoint = glm::vec2(posPlayer.x + 48, posPlayer.y + 17);
					}
					else {
						if (sprite->animation() != MOVE_RIGHT)
							sprite->changeAnimation(MOVE_RIGHT);
					}
				}		
			}
			posPlayer.x += 2;
			if(map->collisionMoveRight(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(2, 0)),
			sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(2, 0)), &posPlayer.y))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
				firePoint = glm::vec2(posPlayer.x + 51, posPlayer.y + 36);
			}
		}
		else if (Game::instance().getKey(122))
		{
			if (!onTheAir) {
				if (Game::instance().getKey(120)) {
					isFiring = true;
					if (goingRight && sprite->animation() != LAY_RIGHT_SHOOTING) {
						direction = glm::vec2(1, 0);
						firePoint = glm::vec2(posPlayer.x + 54, posPlayer.y + 57);
						sprite->changeAnimation(LAY_RIGHT_SHOOTING);
					}
					else if (!goingRight && sprite->animation() != LAY_LEFT_SHOOTING) {
						direction = glm::vec2(-1, 0);
						firePoint = glm::vec2(posPlayer.x + 11, posPlayer.y + 57);
						sprite->changeAnimation(LAY_LEFT_SHOOTING);
					}
				}
				else {
					isFiring = false;
					if (goingRight && sprite->animation() != LAY_RIGHT) {
						firePoint = glm::vec2(posPlayer.x + 54, posPlayer.y + 57);
						sprite->changeAnimation(LAY_RIGHT);
					}
					else if (!goingRight && sprite->animation() != LAY_LEFT) {
						firePoint = glm::vec2(posPlayer.x + 11, posPlayer.y + 57);
						sprite->changeAnimation(LAY_LEFT);
					}
				}
			}
		}
		else if (Game::instance().getKey(100)) { this->takeDamage(1); } //debug per veure les morts
		else
		{
			if (Game::instance().getKey(120)) {
				isFiring = true;
				if (sprite->animation() == MOVE_LEFT || sprite->animation() == LAY_LEFT
					|| sprite->animation() == LAY_LEFT_SHOOTING || sprite->animation() == MOVE_LEFT_SHOOTING
					|| sprite->animation() == STAND_LEFT || sprite->animation() == MOVE_LOOK_DOWN_LEFT
					|| sprite->animation() == MOVE_LOOK_UP_LEFT)
				{
					firePoint = glm::vec2(posPlayer.x + 14, posPlayer.y + 36);
					sprite->changeAnimation(STAND_LEFT_SHOOTING);
					direction = glm::vec2(-1, 0);
				}
				else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == LAY_RIGHT
					|| sprite->animation() == LAY_RIGHT_SHOOTING || sprite->animation() == MOVE_RIGHT_SHOOTING
					|| sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_LOOK_DOWN_RIGHT
					|| sprite->animation() == MOVE_LOOK_UP_RIGHT)
				{
					firePoint = glm::vec2(posPlayer.x + 51, posPlayer.y + 36);
					direction = glm::vec2(1, 0);
					sprite->changeAnimation(STAND_RIGHT_SHOOTING);
				}
			}

			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
				if (Game::instance().getKey(120)) isFiring = true;
				else isFiring = false;
				if (!goingRight && sprite->animation() != LOOK_DOWN_LEFT) {
					firePoint = glm::vec2(posPlayer.x + 9, posPlayer.y + 52);
					sprite->changeAnimation(LOOK_DOWN_LEFT);
					direction = glm::vec2(-1, 1);
				}
				else if (goingRight && sprite->animation() != LOOK_DOWN_RIGHT)
				{
					firePoint = glm::vec2(posPlayer.x + 56, posPlayer.y + 52);
					sprite->changeAnimation(LOOK_DOWN_RIGHT);
					direction = glm::vec2(1, 1);
				}

			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				if (Game::instance().getKey(120)) isFiring = true;
				else isFiring = false;
				if (!goingRight && sprite->animation() != LOOK_UP_LEFT) {
					//firePoint = glm::vec2(posPlayer.x + 9, posPlayer.y + 52);
					//sprite->changeAnimation(LOOK_UP_LEFT);
				}
				else if (goingRight && sprite->animation() != LOOK_UP_RIGHT)
				{
					firePoint = glm::vec2(posPlayer.x + 48, posPlayer.y + 17);
					sprite->changeAnimation(LOOK_UP_RIGHT);
					direction = glm::vec2(1, -1);
				}
			}
			else {
				isFiring = false;
				if (sprite->animation() == MOVE_LEFT || sprite->animation() == LAY_LEFT
					|| sprite->animation() == STAND_LEFT_SHOOTING || sprite->animation() == LOOK_DOWN_LEFT
					|| sprite->animation() == LOOK_UP_LEFT || sprite->animation() == MOVE_LOOK_DOWN_LEFT
					|| sprite->animation() == MOVE_LOOK_UP_LEFT)
				{
					sprite->changeAnimation(STAND_LEFT);
					firePoint = glm::vec2(posPlayer.x + 14, posPlayer.y + 36);
				}
				else if (sprite->animation() == MOVE_RIGHT || sprite->animation() == LAY_RIGHT
					|| sprite->animation() == STAND_RIGHT_SHOOTING || sprite->animation() == LOOK_DOWN_RIGHT
					|| sprite->animation() == LOOK_UP_RIGHT || sprite->animation() == MOVE_LOOK_DOWN_RIGHT
					|| sprite->animation() == MOVE_LOOK_UP_RIGHT)
				{
					firePoint = glm::vec2(posPlayer.x + 51, posPlayer.y + 36);
					sprite->changeAnimation(STAND_RIGHT);

				}
			}
		}
		if (bJumping)
		{
			isFiring = false;
			jumpAngle += JUMP_ANGLE_STEP;
			if (goingRight) {
				if (sprite->animation() != JUMPING_RIGHT)
					sprite->changeAnimation(JUMPING_RIGHT);
			}
			else {
				if (sprite->animation() != JUMPING_LEFT)
					sprite->changeAnimation(JUMPING_LEFT);
			}
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else {
				posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle >= 90)
					bJumping = !map->collisionMoveDown(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0, FALL_STEP)),
					sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0, FALL_STEP)), &posPlayer.y);
			}
		}
		else
		{
			posPlayer.y += FALL_STEP;
			if(map->collisionMoveDown(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE),glm::vec2(0,FALL_STEP)),
			sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(0, FALL_STEP)), &posPlayer.y))
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
				if (Game::instance().getKey(32))
				{
					if (sprite->animation() == MOVE_RIGHT || sprite->animation() == STAND_RIGHT)
						sprite->changeAnimation(JUMPING_RIGHT);
					else if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
						sprite->changeAnimation(JUMPING_LEFT);
					bJumping = true;
					onTheAir = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
			else {
				if (sprite->animation() == STAND_RIGHT || sprite->animation() == STAND_RIGHT_SHOOTING
					|| sprite->animation() == MOVE_RIGHT || sprite->animation() == MOVE_RIGHT_SHOOTING)
					sprite->changeAnimation(JUMPING_RIGHT);
				else if (sprite->animation() == STAND_LEFT || sprite->animation() == STAND_LEFT_SHOOTING
					|| sprite->animation() == MOVE_LEFT || sprite->animation() == MOVE_LEFT_SHOOTING)
					sprite->changeAnimation(JUMPING_LEFT);
				onTheAir = true;
			}
			
		}

		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
	else {
		sprite->changeAnimation(DYING);
	}
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

bool Player::isEndOfLevel() {
	return map->onEndOfLevel(posPlayer, glm::ivec2(P_SIZE, P_SIZE));
}

int Player::min(int a, int b) {
	int ret;
	if (a <= b) ret = a;
	else ret = b;
	return ret;
}

void Player::takeDamage(int dmg) {
	health -= dmg;
	if (health <= 0) {
		dead = true;
		health = 1;
		sprite->changeAnimation(JUMPING_RIGHT);
	}
}


