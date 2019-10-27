#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Sprite.h"

//debug
#include <fstream>
#include <iostream>


Sprite *Sprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet,
	Texture *spritesheet, ShaderProgram *program)
{
	Sprite *quad = new Sprite(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}


Sprite::Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	float vertices[24] = {0.f, 0.f, 0.f, 0.f, 
												quadSize.x, 0.f, sizeInSpritesheet.x, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, 0.f, 0.f, 0.f, 
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y, 
												0.f, quadSize.y, 0.f, sizeInSpritesheet.y};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
	position = glm::vec2(0.f);
}

void Sprite::update(int deltaTime)
{
	if(currentAnimation >= 0)
	{
		timeAnimation += deltaTime;
		while(timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}

void Sprite::render() const
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void Sprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void Sprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
}

void Sprite::setAnimationSpeed(int animId, int keyframesPerSec)
{
	if(animId < int(animations.size()))
		animations[animId].millisecsPerKeyframe = 1000.f / keyframesPerSec;
}

void Sprite::addKeyframe(int animId, const glm::vec2 &displacement)
{
	if(animId < int(animations.size()))
		animations[animId].keyframeDispl.push_back(displacement);
}

void Sprite::changeAnimation(int animId)
{
	if(animId < int(animations.size()))
	{
		currentAnimation = animId;
		currentKeyframe = 0;
		timeAnimation = 0.f;
		texCoordDispl = animations[animId].keyframeDispl[0];
	}
}

int Sprite::animation() const
{
	return currentAnimation;
}

glm::vec2 Sprite::getRealMinPos(const glm::vec2& mySize)
{
	glm::vec2 margin = glm::vec2(mySize.x*0.1,mySize.y*0.05);
	
	glm::vec2 offPos = position;

	glm::vec2 displ = animations[currentAnimation].keyframeDispl[currentKeyframe];

	//busquem y minima
	for (int y = margin.y; y < (mySize.y-margin.y); y++) {
		for (int x = margin.x; x < (mySize.x-margin.x); x++) {
			if (texture->getPixel(x - margin.x + displ.x, y - margin.y + displ.y).getAlpha() > 256 * 3 / 4)
				offPos.y =  y;
		}
	}
	//busquem x minim
	for (int x = margin.x; x < (mySize.x - margin.x); x++) {
		for (int y = margin.y; y < (mySize.y - margin.y); y++) {
			if (texture->getPixel(x - margin.x + displ.x, y - margin.y + displ.y).getAlpha() > 256 * 3 / 4)
				offPos.x = x;
		}
	}

	return offPos + position;
}

glm::vec2 Sprite::getRealSize(const glm::vec2& mySize)
{
	glm::vec2 margin = glm::vec2(mySize.x * 0.1, mySize.y * 0.05);

	glm::vec2 maxOffPos = position;

	glm::vec2 displ = animations[currentAnimation].keyframeDispl[currentKeyframe];

	//busquem y max
	for (int y = mySize.y-margin.y; y > margin.y; y--) {
		for (int x = mySize.x-margin.x; x > margin.x; x--) {
			if (texture->getPixel(x + margin.x + displ.x, y + margin.y + displ.y).getAlpha() > 256 * 3 / 4)
				maxOffPos.y = y;
		}
	}
	//busquem x max
	for (int x = mySize.x - margin.x; x > margin.x; x--) {
		for (int y = mySize.y-margin.y; y > margin.y; y--) {
			if (texture->getPixel(x + margin.x + displ.x, y + margin.y + displ.y).getAlpha() > 256 * 3 / 4)
				maxOffPos.x = x;
		}
	}
	ofstream out;
	out.open("myDebug/col.txt", ios::app);
	out << "My Size : " << (maxOffPos + position - getRealMinPos(mySize)).x << " " << (maxOffPos + position - getRealMinPos(mySize)).y << endl;
	out << "My pos: " << getRealMinPos(mySize).x << " " << getRealMinPos(mySize).y << endl;
	out.close();

	return (maxOffPos + position - getRealMinPos(mySize));
}

void Sprite::setPosition(const glm::vec2 &pos)
{
	position = pos;
}



