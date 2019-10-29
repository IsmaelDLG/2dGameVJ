#pragma once
#include "Player.h"


class Kimkoh :
	public Player
{
public:
	void init(const string& path, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;
	void render() override;
	void reduceHealth(int dmg);

	bool isKilled() { return death; };
private:
	bool death;
};

