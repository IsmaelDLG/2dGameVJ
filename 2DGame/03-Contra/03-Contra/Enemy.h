#include "Player.h"

class Enemy: public Player
{
public:

	void init_stats();
	void update(int deltaTime, Player* pc);
	void reduceDamage(int dmg);
	void shootNow();

	glm::vec2 aimingAt();
	bool isKilled() { return death; }
	bool isShooting() { return shoot; }

private:

	int life;
	int reload;
	bool death;
	bool shoot;
	glm::vec2 aim;
};


