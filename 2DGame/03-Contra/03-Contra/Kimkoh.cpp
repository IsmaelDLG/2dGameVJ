#include "Kimkoh.h"
//debug
#include <fstream>

#define P_SIZE 128

enum KimkohAnims {
	BASIC_ATAC,DIE
};
void Kimkoh::init(const string& path, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	tileMapDispl = glm::vec2(0, 0);
	health = 10;
	dead = false;
	spritesheet = new Texture();
	spritesheet->loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(P_SIZE, P_SIZE), glm::vec2(1.f / 4.f, 1.f / 4.f),spritesheet, &shaderProgram);
	this->setPosition(tileMapPos);
	
	
	sprite->setNumberAnimations(2);
	//animació d'atac base
	sprite->setAnimationSpeed(BASIC_ATAC, 6);
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(1.f /4.f , 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(1.f / 4.f * 2.f, 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(1.f / 4.f * 3.f, 0.f));
	//animació de mort
	sprite->setAnimationSpeed(DIE, 2);
	sprite->addKeyframe(DIE, glm::vec2(0.f, 1.f / 4.f));
	sprite->addKeyframe(DIE, glm::vec2(1.f / 4.f, 1.f/4.f));
	sprite->addKeyframe(DIE, glm::vec2(1.f / 4.f * 2.f, 1.f / 4.f));
	sprite->addKeyframe(DIE, glm::vec2(1.f / 4.f * 3.f, 1.f / 4.f));


	sprite->changeAnimation(BASIC_ATAC);
	sprite->setPosition(glm::vec2(tileMapPos.x, tileMapPos.y));
	posPlayer = tileMapPos;
	firePoint = posPlayer;
}

void Kimkoh::update(int deltaTime, Player* pc)
{
	

	if (pc->thereIsColision(sprite->getRealMinPos(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-1, 0)),
		sprite->getRealSize(glm::vec2(P_SIZE, P_SIZE), glm::vec2(-1, 0)))) {
		pc->takeDamage(1);
	}
	
	if (isDead()) {
		if (timer > 0) {
			timer -= 1;
			if (sprite->animation() != DIE) {
				sprite->changeAnimation(DIE);
			}
		}
	}
	else {
		if (sprite->animation() != BASIC_ATAC)
			sprite->changeAnimation(BASIC_ATAC);
	}
	sprite->update(deltaTime);

}

void Kimkoh::render()
{
	sprite->render();
}

void Kimkoh::reduceHealth(int dmg)
{
	health -= dmg;
	if (health <= 0) {
		dead = true;
		//temps hardcoded
		timer = 115;
	}
}

int Kimkoh::timerZero()
{
	return timer;
}


