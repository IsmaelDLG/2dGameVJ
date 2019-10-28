#include "Kimkoh.h"
//debug
#include <fstream>

#define P_SIZE 128

enum KimkohAnims {
	BASIC_ATAC,IDLE,DIE
};
void Kimkoh::init(const string& path, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	tileMapDispl = glm::vec2(0, 0);
	health = 500;
	spritesheet = new Texture();
	spritesheet->loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(P_SIZE, P_SIZE), glm::vec2(1.f / 4.f, 1.f / 4.f),spritesheet, &shaderProgram);
	this->setPosition(tileMapPos);
	
	
	sprite->setNumberAnimations(1);
	//animació d'atac base
	sprite->setAnimationSpeed(BASIC_ATAC, 8);
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(1.f /4.f , 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(1.f / 4.f * 2.f, 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(1.f / 4.f * 3.f, 0.f));
	
	sprite->changeAnimation(BASIC_ATAC);
	sprite->setPosition(glm::vec2(tileMapPos.x, tileMapPos.y));
	posPlayer = tileMapPos;
	firePoint = posPlayer;
}

void Kimkoh::update(int deltaTime)
{
	ofstream out;
	out.open("myDebug/Kimkoh.txt", ios::app);
	out << this->getPlayerPos().x << " " << this->getPlayerPos().y << endl << endl;
	if (sprite->animation() != BASIC_ATAC)
		sprite->changeAnimation(BASIC_ATAC);
	sprite->update(deltaTime);
	out.close();
}

void Kimkoh::render()
{
	sprite->render();
}


