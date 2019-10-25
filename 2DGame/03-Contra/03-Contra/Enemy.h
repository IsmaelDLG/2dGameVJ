#include "Player.h"

class Enemy: public Player
{
public:
	void update(int deltaTime) override;
};

