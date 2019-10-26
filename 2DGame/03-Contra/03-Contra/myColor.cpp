#include "myColor.h"
#include <fstream>

myColor::myColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
}

myColor::~myColor()
{
}

unsigned int myColor::getAlpha()
{

	return alpha;
}

unsigned int myColor::getBlack()
{
	//negre = 1/ligtness
	//convertim a hsl i retornem el negre
	//mantenim la resolucio de 256
	
	return (max(red, green, blue)+min(red,green,blue))/2;
}

unsigned int myColor::getGreen()
{
	return green;
}

unsigned int myColor::max(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int aux;
	if (r >= b && r >= g) aux = r;
	else if (b >= r && b >= g) aux = b;
	else aux = g;
	return aux;
}

unsigned int myColor::min(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int aux;
	if (r <= b && r <= g) aux = r;
	else if (b <= r && b <= g) aux = b;
	else aux = g;
	return aux;
}