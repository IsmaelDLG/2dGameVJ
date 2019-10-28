#include "Player.h"

class Enemy: public Player
{
public:

	void init_stats();
	void update(int deltaTime) override;
	void reduceDamage(int dmg);

	bool isKilled() { return death; }

private:

	int life;
	bool death;
};


