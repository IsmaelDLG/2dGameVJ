#include "Player.h"

class Enemy: public Player
{
public:

	void init_stats();
	void update(int deltaTime) override;
	void takeDamage(int dmg);

	bool isDead() { return dead; }

private:

	int health;
	bool dead;
};


