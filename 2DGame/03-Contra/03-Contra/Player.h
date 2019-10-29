#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "Level.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	virtual void init(const string& path, const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();
	
	void setMap(Level* myMap);
	void setPosition(const glm::vec2 &pos);
	void takeDamage(int dmg);
	void setState(bool isdead) { dead = isdead; }
	void setFiring(bool stop) { isFiring = stop; }
	void activateSG() { spreadGun = true; }

	int min(int a, int b);
	bool getisFiring() { return isFiring; }
	bool isDead() { return dead; }
	int getVides() { return life; }
	bool spreadGunOn() { return spreadGun; }
	bool isEndOfLevel();
	bool thereIsColision(glm::vec2 obj, glm::vec2 size);
	glm::vec2 getPlayerPos() { return posPlayer; }
	glm::vec2 getFirePoint() { return firePoint; }
	glm::vec2 getdirection() { return direction; }
	


private:
	bool bJumping, isFiring, onTheAir, goingRight, spreadGun;
	int jumpAngle, startY, jumpColide;
	int life;
protected:
	Sprite* sprite;
	Texture* spritesheet;
	glm::ivec2 posPlayer, tileMapDispl, firePoint, direction;
	int health;
	bool dead;
	Level* map;
};


#endif // _PLAYER_INCLUDE


