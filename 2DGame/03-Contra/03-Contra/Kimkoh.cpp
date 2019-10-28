#include "Kimkoh.h"
//debug
#include <fstream>

#define P_SIZE 128

enum KimkohAnims {
	BASIC_ATAC,IDLE,DIE
};
void Kimkoh::init(const string& path, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	firePoint = posPlayer;
	tileMapDispl = glm::vec2(0, 0);
	health = 500;
	Texture* sheet = new Texture();
	sheet->loadFromFile(path, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(P_SIZE, P_SIZE), glm::vec2(sheet->width() / 4, sheet->height()),sheet, &shaderProgram);
	this->setPosition(tileMapPos);
	
	sprite->setNumberAnimations(1);
	//animació d'atac base
	sprite->setAnimationSpeed(BASIC_ATAC, 8);
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(sheet->width()/4, 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(sheet->width() / 4 * 2, 0.f));
	sprite->addKeyframe(BASIC_ATAC, glm::vec2(sheet->width() / 4 * 3, 0.f));
	
	sprite->changeAnimation(BASIC_ATAC);
	sprite->setPosition(tileMapPos);
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


