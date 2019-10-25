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
	virtual void update(int deltaTime);
	void render();
	
	void setMap(Level* myMap);
	void setPosition(const glm::vec2 &pos);
	int min(int a, int b);
	glm::vec2 getPlayerPos() { return posPlayer; }
	
private:
	bool bJumping;
	bool onTheAir, goingRight, spraygun;
	int jumpAngle, startY;
	Texture spritesheet;
protected:
	Sprite* sprite;
	glm::ivec2 posPlayer, tileMapDispl;
	Level* map;
};


#endif // _PLAYER_INCLUDE


