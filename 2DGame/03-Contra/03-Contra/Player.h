#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "Level.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setMap(Level* myMap);
	void setPosition(const glm::vec2 &pos);
	void takeDamage(int dmg);
	void setState(bool alive) { dead = alive; }
	void setFiring(bool stop) { isFiring = stop; }
	int min(int a, int b);
	glm::vec2 getPlayerPos() { return posPlayer; }
	bool isDead() { return dead; }
	glm::vec2 getFirePoint() { return firePoint; }
	bool getisFiring() { return isFiring; }
	
private:
	bool bJumping, dead, isFiring;
	bool onTheAir, goingRight, spreadGun;
	glm::ivec2 tileMapDispl, posPlayer, firePoint;
	int jumpAngle, startY, jumpColide;
	int health, life;
	Texture spritesheet;
	Sprite *sprite;
	Level *map;

};


#endif // _PLAYER_INCLUDE


