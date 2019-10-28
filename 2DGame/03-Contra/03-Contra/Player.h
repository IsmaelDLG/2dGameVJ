#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "Level.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const string& path, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	void render();
	
	void setMap(Level* myMap);
	void setPosition(const glm::vec2 &pos);
	void takeDamage(int dmg);
	void setState(bool alive) { dead = alive; }
	void setFiring(bool stop) { isFiring = stop; }
	void activateSG() { spreadGun = true; }

	int min(int a, int b);
	bool getisFiring() { return isFiring; }
	bool isDead() { return dead; }
	bool spreadGunOn() { return spreadGun; }
	bool isEndOfLevel();
	bool thereIsColision(glm::vec2 obj, int size);
	glm::vec2 getPlayerPos() { return posPlayer; }
	glm::vec2 getFirePoint() { return firePoint; }
	glm::vec2 getdirection() { return direction; }
	


private:
	bool bJumping, dead, isFiring, onTheAir, goingRight, spreadGun;
	glm::ivec2 firePoint, direction;
	int jumpAngle, startY, jumpColide;
	int health, life;
	Texture spritesheet;
protected:
	Sprite* sprite;
	glm::ivec2 posPlayer, tileMapDispl;
	Level* map;
};


#endif // _PLAYER_INCLUDE


